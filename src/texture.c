// #include "texture.h"
// #include <SDL_image.h>
// #include "jsonManager.h"
// #include "config.h"

// SDL_Texture* load_texture_from_path (SDL_Renderer *ren, char *path) {
//     SDL_Surface *surface = IMG_Load(path);
//     if (!surface) {
//         printf("Error loading texture from path: %s. Falling back to missing texture.\n", path);
//         return NULL;
//     }

//     SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
//     SDL_FreeSurface(surface);

//     if (!texture) {
//         printf("Error creating texture from surface: %s\n", SDL_GetError());
//         return NULL;
//     }

//     return texture;
// }


// SDL_Texture* load_texture (SDL_Renderer *ren, char *textureKey) {
//     // Load the JSON file
//     char* jsonContent = read_file(CONFIG_PATH);
//     if (!jsonContent) {
//         printf("Error reading resources.json\n");
//         return NULL;
//     }

//     // Parse the JSON file
//     struct json_object *jsonObject = json_tokener_parse(jsonContent);
//     if (!jsonObject) {
//         printf("Error parsing JSON\n");
//         free(jsonContent);
//         return NULL;
//     }
    
//     // Get the texture path from the JSON object
//     char *texturePath = get_nested_value(jsonObject, textureKey);
//     if (!texturePath) {
//         printf("Error retrieving texture path for key: %s\n", textureKey);
//         json_object_put(jsonObject);
//         free(jsonContent);
//         return NULL;
//     }

//     // Try to load the requested texture
//     SDL_Surface *surface = IMG_Load(texturePath);
//     if (!surface) {
//         printf("Error loading texture from path: %s. Falling back to missing texture.\n", texturePath);

//         // Fallback to missing texture
//         char* fallbackKey = "textures/missing_texture";
//         char *fallbackPath = get_nested_value(jsonObject, fallbackKey);
        
//         if (!fallbackPath) {
//             printf("Error retrieving fallback texture path for key: %s\n", fallbackKey);
//             json_object_put(jsonObject);
//             free(jsonContent);
//             return NULL;  // If the fallback texture path is missing, return NULL
//         }

//         // Load the fallback texture
//         surface = IMG_Load(fallbackPath);
//         if (!surface) {
//             printf("Error loading fallback texture from path: %s\n", fallbackPath);
//             json_object_put(jsonObject);
//             free(jsonContent);
//             return NULL;
//         }
//     }

//     // Create the texture from the surface
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
//     if (!texture) {
//         printf("Error creating texture from surface: %s\n", SDL_GetError());
//         SDL_FreeSurface(surface);
//         json_object_put(jsonObject);
//         free(jsonContent);
//         return NULL;
//     }

//     SDL_FreeSurface(surface);
//     json_object_put(jsonObject);
//     free(jsonContent);

//     return texture;
// }