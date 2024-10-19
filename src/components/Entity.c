#include "../components/Entity.h"
#include "../components/Collider.h"

#include "../Config.h"

#include "../managers/ResourceManager.h"
#include "../managers/MemoryManager.h"

Entity* init_entity(SDL_Renderer *ren,
                    ResourceManager *resourceManager,
                    int speed,
                    int velX,
                    int velY) {
    Entity *entity = (Entity*)allocateMemory(sizeof(Entity));
    if (entity == NULL) {
        printf("Failed to allocate memory for entity\n");
        return NULL;
    }

    entity->speed = speed;
    entity->velX = velX;
    entity->velY = velY;

    entity->rect.h = CHARACTER_HEIGHT;
    entity->rect.w = CHARACTER_WIDTH;
    entity->rect.x = SCREEN_WIDTH / 2.0f;
    entity->rect.y = SCREEN_HEIGHT / 2.0f;

    // Loading entity texture
    entity->texture = get_texture(resourceManager, "missing_texture");
    if (!entity->texture) {
        printf("Failed to load entity texture or fallback texture\n");
    }

    entity->posAccumulator.x = SCREEN_WIDTH / 2.0f;
    entity->posAccumulator.y = SCREEN_HEIGHT / 2.0f;
    
    entity->collider.rect = entity->rect;
    entity->collider.isCircle = 0;
    entity->collider.radius = 0;

    return entity;
}

void update_entities(Entity *entities[], float deltaTime, int entityCount) {
    if (entities != NULL) {
        // Update entities
        for (size_t i = 0; i < entityCount; i++)
        {
            if (entities[i] != NULL) {
                entities[i]->posAccumulator.x += entities[i]->velX * deltaTime;
                entities[i]->posAccumulator.y += entities[i]->velY * deltaTime;
                // printf("Entity (%f) position: (%f, %f)\n", (double)i, entities[i]->posAccumulator.x, entities[i]->posAccumulator.y);

            }
            else {
                // Don't proceed if entity is NULL
                printf("Warning: Tried to update a NULL entity at index %d\n", (int)i);
            }
        }
        return;
    }
}

void render_entity(SDL_Renderer* ren, Entity *entity) {
    entity->rect.x = (int)(entity->posAccumulator.x);
    entity->rect.y = (int)(entity->posAccumulator.y);
    if (entity->texture) {
        SDL_RenderCopy(ren, entity->texture, NULL, &entity->rect);
    }
}

void free_entities(Entity *entities[], int *entityCount) {
    if (entities) {
        // Free each entity and set the pointer to NULL
        for (size_t i = 0; i < *entityCount; i++) {
            if (entities[i]) {
                if (entities[i]->texture) {
                    SDL_DestroyTexture(entities[i]->texture); // Free associated texture
                }
                freeMemory(entities[i]);  // Free the entity itself
                entities[i] = NULL; // Set pointer to NULL for safety
            }
        }
    }

    // Reset entity count to 0
    *entityCount = 0; 
}
