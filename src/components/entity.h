#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "../components/collider_component.h"
#include "../components/player.h"

#include "../managers/resource_manager.h"

// Generic entity
typedef struct {
    int speed;
    int velX;
    int velY;
    SDL_Rect rect;
    SDL_Texture *texture;
    Collider collider;
    PositionAccumulator position_accumulator;
} Entity;

Entity* init_entity(SDL_Renderer *ren, ResourceManager *resource_manager, int speed, int velX, int velY);
void update_entities(Entity *entities[], float delta_time, int entityIndex);
void render_entity(SDL_Renderer* ren, Entity *entity);
void free_entity(Entity *entity);
void free_entities(Entity *entities[], int *entity_count);

#endif