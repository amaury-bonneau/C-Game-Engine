#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "../components/Collider.h"
#include "../components/Player.h"

#include "../managers/ResourceManager.h"

// Generic entity
typedef struct {
    int speed;
    int velX;
    int velY;
    SDL_Rect rect;
    SDL_Texture *texture;
    Collider collider;
    PositionAccumulator posAccumulator;
} Entity;

Entity* init_entity(SDL_Renderer *ren, ResourceManager *resourceManager, int speed, int velX, int velY);
void update_entities(Entity *entities[], float deltaTime, int entityIndex);
void render_entity(SDL_Renderer* ren, Entity *entity);
void free_entity(Entity *entity);
void free_entities(Entity *entities[], int *entityCount);

#endif