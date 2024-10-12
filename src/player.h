#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "collider.h"
#include "resourceManager.h"

// This structure is an accumulator for floating point player coordinates (used in order to avoid jittery movement) 
typedef struct {
    float x;
    float y;
} PositionAccumulator;

// Player entity
typedef struct {
    int speed;
    int velX;
    int velY;
    SDL_Rect rect;
    SDL_Texture *texture;
    PositionAccumulator posAccumulator;
    Collider collider;
} Player;

Player* init_player(SDL_Renderer *ren, ResourceManager *resourceManager, int speed, int velX, int velY);
void update_player(Player *player, float deltaTime);
void render_player(SDL_Renderer* ren, Player *player);
void free_player(Player *player);

#endif