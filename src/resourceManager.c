#include "resourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include "jsonManager.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>



ResourceManager* load_resources(SDL_Renderer *ren) {

    // Initialize resource manager
    ResourceManager *resourceManager = (ResourceManager*)malloc(sizeof(ResourceManager));
    if (resourceManager == NULL) {
        SDL_Log("Failed to allocate ResourceManager");
        return NULL;
    }

    resourceManager->textureCount = 0;
    resourceManager->otherResource = NULL;

    // Read the JSON file
    char* jsonContent = read_file(CONFIG_PATH);
    if (jsonContent == NULL) {
        SDL_Log("Failed to read JSON file");
        free(resourceManager);
        return NULL;
    }

    // Parse the JSON data
    struct json_object *jsonObject = json_tokener_parse(jsonContent);
    if (jsonObject == NULL) {
        SDL_Log("Failed to parse JSON data");
        free(jsonContent);
        free(resourceManager);
        return NULL;
    }

    // Load textures
    struct json_object *texturesObject = get_json_value_from_key(jsonObject, "textures");
    if (!texturesObject) {
        SDL_Log("Failed to find 'textures' object in JSON");
        json_object_put(jsonObject);
        free(jsonContent);
        free(resourceManager);
        return NULL;
    }

    const char** textureKeys = get_keys_from_json(texturesObject);
    int numKeys = json_object_object_length(texturesObject);

    // Iterate over textureKeys and load textures
    for (int i = 0; i < numKeys && resourceManager->textureCount < MAX_TEXTURES; i++) {
        char keyPath[256];  // Holds the full JSON key path
        snprintf(keyPath, sizeof(keyPath), "textures/%s", textureKeys[i]);

        const char *filePath = get_nested_value(jsonObject, keyPath);
        if (filePath == NULL) {
            SDL_Log("Failed to get texture path from JSON for key: %s", textureKeys[i]);
            continue;
        }

        SDL_Surface *surface = IMG_Load(filePath);
        if (!surface) {
            SDL_Log("Failed to load texture surface for key: %s, SDL Error: %s", textureKeys[i], SDL_GetError());
            continue;
        }

        // Create a texture from the surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);  // Free surface after creating texture
        if (!texture) {
            SDL_Log("Failed to create texture for key: %s, SDL Error: %s", textureKeys[i], SDL_GetError());
            continue;
        }

        // Allocate memory for the TextureEntry
        TextureEntry *entry = (TextureEntry*)malloc(sizeof(TextureEntry));
        if (!entry) {
            SDL_Log("Failed to allocate memory for texture entry: %s", textureKeys[i]);
            SDL_DestroyTexture(texture);  // Cleanup texture if allocation fails
            continue;
        }

        // Duplicate the key string and store the texture and key in the entry
        entry->key = strdup(textureKeys[i]);
        if (!entry->key) {
            SDL_Log("Failed to allocate memory for key: %s", textureKeys[i]);
            SDL_DestroyTexture(texture);  // Cleanup texture
            free(entry);  // Cleanup entry
            continue;
        }
        entry->texture = texture;

        // Add to the resourceManager's texture array
        resourceManager->textures[resourceManager->textureCount] = entry;
        resourceManager->textureCount++;  // Increment texture count
    }

    // Cleanup JSON data
    free(textureKeys);
    json_object_put(jsonObject);
    free(jsonContent);

    return resourceManager;
}

SDL_Texture* get_texture(ResourceManager* resourceManager, const char* key) {
    // Search through the textures to find the matching key
    for (int i = 0; i < resourceManager->textureCount; i++) {
        if (strcmp(resourceManager->textures[i]->key, key) == 0) {
            return resourceManager->textures[i]->texture;
        }
    }

    printf("Error loading texture from key: %s. Falling back to missing texture.\n", key);

    const char *fallbackTextureKey = "missing_texture"; 
    for (int i = 0; i < resourceManager->textureCount; i++) {
        if (strcmp(resourceManager->textures[i]->key, fallbackTextureKey) == 0) {
            return resourceManager->textures[i]->texture;
        }
    }

    printf("Error loading missing texture.");
    return NULL;  // Texture not found
}

void unload_textures(ResourceManager* resourceManager) {
    // Free all textures and their associated memory
    for (int i = 0; i < resourceManager->textureCount; i++) {
        if (resourceManager->textures[i]) {
            if (resourceManager->textures[i]->texture) {
                SDL_DestroyTexture(resourceManager->textures[i]->texture);  // Destroy the SDL texture
                resourceManager->textures[i]->texture = NULL;  // Avoid dangling pointer
            }
            if (resourceManager->textures[i]->key) {
                free(resourceManager->textures[i]->key);  // Free the key string
                resourceManager->textures[i]->key = NULL;  // Avoid dangling pointer
            }
            free(resourceManager->textures[i]);  // Free the TextureEntry
            resourceManager->textures[i] = NULL;  // Avoid dangling pointer
        }
    }
    resourceManager->textureCount = 0;  // Reset texture count
}

void unload_resources(ResourceManager* resourceManager) {
    // Unload all textures
    unload_textures(resourceManager);

    // Free other resources, if any (e.g., otherResource)
    if (resourceManager->otherResource) {
        free(resourceManager->otherResource);
    }

    // Finally, free the resource manager itself
    free(resourceManager);
}
