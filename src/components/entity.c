#include "../components/entity.h"
#include "../components/collider_component.h"

#include "../config.h"

#include "../managers/resource_manager.h"
#include "../managers/memory_manager.h"

Entity* init_entity(SDL_Renderer *ren,
                    ResourceManager *resource_manager,
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
    entity->texture = get_texture(resource_manager, "missing_texture");
    if (!entity->texture) {
        printf("Failed to load entity texture or fallback texture\n");
    }

    entity->position_accumulator.x = SCREEN_WIDTH / 2.0f;
    entity->position_accumulator.y = SCREEN_HEIGHT / 2.0f;
    
    entity->collider.rect = entity->rect;
    entity->collider.isCircle = 0;
    entity->collider.radius = 0;

    return entity;
}

void update_entities(Entity *entities[], float delta_time, int entity_count) {
    if (entities != NULL) {
        // Update entities
        for (size_t i = 0; i < (size_t)entity_count; i++)
        {
            if (entities[i] != NULL) {
                entities[i]->position_accumulator.x += entities[i]->velX * delta_time;
                entities[i]->position_accumulator.y += entities[i]->velY * delta_time;
                // printf("Entity (%f) position: (%f, %f)\n", (double)i, entities[i]->position_accumulator.x, entities[i]->position_accumulator.y);

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
    entity->rect.x = (int)(entity->position_accumulator.x);
    entity->rect.y = (int)(entity->position_accumulator.y);
    if (entity->texture) {
        SDL_RenderCopy(ren, entity->texture, NULL, &entity->rect);
    }
}

void free_entities(Entity *entities[], int *entity_count) {
    if (entities) {
        // Free each entity and set the pointer to NULL
        for (size_t i = 0; i < (size_t)*entity_count; i++) {
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
    *entity_count = 0; 
}
