#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "resourceManager.h"

#include <SDL.h>

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
} Background;


Background init_background(SDL_Renderer *ren, ResourceManager *resourceManager);
void render_background(SDL_Renderer *ren, Background *background);
void free_background(Background *background);

#endif