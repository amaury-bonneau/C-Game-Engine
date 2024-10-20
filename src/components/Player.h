#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "../components/collider_component.h"
#include "../managers/resource_manager.h"

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
    PositionAccumulator position_accumulator;
    Collider collider;
} Player;

Player* init_player(SDL_Renderer *ren, ResourceManager *resourceManager, int speed, int velX, int velY);
void update_player(Player *player, float delta_time);
void render_player(SDL_Renderer* ren, Player *player);
void free_player(Player *player);

#endif