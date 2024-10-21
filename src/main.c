#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "main.h"
#include "logic.h"
#include "components/player.h"
#include "components/entity.h"
#include "components/collider_component.h"
#include "components/background.h"
#include "config.h"

#include "managers/resource_manager.h"

int main(int argc, char *argv[]) {

    SDL_Window* win = NULL;
    SDL_Renderer* ren = NULL;
    ResourceManager* resource_manager = NULL;

    Player* player = NULL;
    Background* background = NULL;

    // Entity storing
    Entity* entities[MAX_ENTITIES];
    int entity_count = 0;

    win = create_window();
    if (!win) {
        terminate_program(background, player, entities, &entity_count, ren, win, resource_manager);
        return_with_delay(1);
    }
    ren = create_renderer(win);
    if (!ren) {
        terminate_program(background, player, entities, &entity_count, ren, win, resource_manager);
        return_with_delay(1);
    }
    // Set logical size for initial window size
    SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize resource_manager
    resource_manager = load_resources(ren);

    // Initialize Background
    background = init_background(ren, resource_manager);

    // Initialize Player
    int speed = 200;
    int velX = 0, velY = 0;
    player = init_player(ren, resource_manager, speed, velX, velY);

    float delta_time = 0;
    float last_time = SDL_GetTicks() / 1000.0f; // initializing last_time right at start so delta_time has a meaningful value
    
    // Initialize entities
    Entity *obstacle = init_entity(ren, resource_manager, speed, velX, velY);
    if (obstacle == NULL) {
        printf("Failed to initialize entity\n");
        terminate_program(background, player, entities, &entity_count, ren, win, resource_manager);
        return_with_delay(1);  // Exit early if entity creation failed
    }
    if (entity_count < MAX_ENTITIES) {
        entities[entity_count++] = obstacle;
    } else {
        printf("Error: max number of entities attained.");
    }
    
    main_loop(ren, win, player, background, entities, entity_count, last_time, delta_time);

    terminate_program(background, player, entities, &entity_count, ren, win, resource_manager);
    return_with_delay(100);
}
