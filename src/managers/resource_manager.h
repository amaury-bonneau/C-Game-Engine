#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL.h>

#define MAX_TEXTURES 100

typedef struct {
    char *key;
    SDL_Texture *texture;
} TextureEntry;

typedef struct {
    TextureEntry *textures[MAX_TEXTURES];
    int textureCount;
    char* otherResource; // Any other configuration
} ResourceManager;

ResourceManager* load_resources(SDL_Renderer* ren);
SDL_Texture* get_texture(ResourceManager* resource_manager, const char* key);
void unload_textures(ResourceManager* resource_manager);
void unload_resources(ResourceManager* resource_manager);

#endif