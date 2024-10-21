#include <SDL.h>
#include <SDL_image.h>

#include "components/player.h"
#include "components/entity.h"
#include "components/background.h"
#include "managers/resource_manager.h"

#include "logic.h"
#include "config.h"

void main_loop(SDL_Renderer* ren, SDL_Window* win, Player* player, Background* background, Entity* entities[], int entity_count, float last_time, float delta_time) {
    // Main loop flag
    int *quit = 0;
    SDL_Event e;
    
    // Main loop
    while (!quit) {
        float current_time = SDL_GetTicks() / 1000.0f; // The number of seconds elapsed since init of SDL lib at start of the program
        delta_time = current_time - last_time; // The delta between current frame time and previous frame time
        if (delta_time > 0.1f) delta_time = 0.1f;  // Cap delta_time at 0.1 seconds to avoid problematic enormous or minuscule values
        last_time = current_time;

        // Handle CI/CD timeout
        if (isRunningInCI()) check_timeout(current_time, quit);

        // Handle input
        handle_input(e, player, quit, win, ren);

        // Update logic (player position, etc.)
        update(player, entities, entity_count, delta_time);

        // Check for collisions
        // for (size_t i = 0; i < entity_count; i++)
        // {
        //     if (check_collisions(&player->collider, &entities[i]->collider)) {
        //         printf("collision détectée between player and entity n°%zu \n", i);
        //     }
        // }

        // Render everything
        render_textures(ren, background, player, entities);

    }
}


void update(Player *player, Entity *entities[], int entity_count, float delta_time) {
    update_player(player, delta_time);
    // update_entities(entities, delta_time, entity_count);
}

void terminate_program(Background *background, Player *player, Entity *entities[], int *entity_count, SDL_Renderer *ren, SDL_Window *win, ResourceManager *resource_manager) {
    printf("Terminating program...\n");

    if (resource_manager) {
        printf("Unloading resources...\n");
        unload_resources(resource_manager);
    }

    // Free game-specific resources
    if (background) {
        printf("Freeing background...\n");
        free_background(background);
    }
    
    if (player) {
        printf("Freeing player...\n");
        free_player(player);

    }

    if (entities) {
        printf("Freeing entities...\n");
        free_entities(entities, entity_count);
    }

    // Free SDL-specific resources (renderer before window)
    if (ren) {
        printf("Destroying renderer...\n");
        SDL_DestroyRenderer(ren);
    }
    
    if (win) {
        printf("Destroying window...\n");
        SDL_DestroyWindow(win);
    }

    // Quit SDL subsystems in correct order
    IMG_Quit();
    SDL_Quit();
    
    printf("Program terminated.\n");
}

void render_textures(SDL_Renderer* ren, Background *background, Player *player, Entity *entities[]) {
        // Clear screen
        SDL_RenderClear(ren);

        // Render the background
        render_background(ren, background);

        // Render the player 
        if (player != NULL) {
            render_player(ren, player);
        }
        
        // Render the entities 
        if (entities != NULL) {
            entities[0]->rect.x = (int)(entities[0]->position_accumulator.x);
            entities[0]->rect.y = (int)(entities[0]->position_accumulator.y);
            render_entity(ren, entities[0]);
        }
        
        // Update screen
        SDL_RenderPresent(ren);
}

void handle_input(SDL_Event e, Player *player, int *quit, SDL_Window *win, SDL_Renderer *ren) {
    // Event handling
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            printf("SDL_QUIT event received.\n");
            *quit = 1;
        }

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) { // simulated keyboard keys
                case SDLK_UP: player->velY = -player->speed; break;
                case SDLK_DOWN: player->velY = player->speed; break;
                case SDLK_LEFT: player->velX = -player->speed; break;
                case SDLK_RIGHT: player->velX = player->speed; break;

                case SDLK_ESCAPE: *quit = 1; break;
                case SDLK_RETURN: if(e.key.keysym.mod & KMOD_ALT) { toggle_fullscren(win, ren); } break;

                default: printf("Unhandled key: %d\n", e.key.keysym.sym); break;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN: player->velY = 0; break;
                case SDLK_LEFT:
                case SDLK_RIGHT: player->velX = 0; break;

                default: printf("Unhandled key: %d\n", e.key.keysym.sym); break;
            }
        }
    }
}

SDL_Window* create_window() {
    // Create an SDL window

    SDL_Window *win = SDL_CreateWindow("Game",
                                        100,
                                        100,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN |
                                        SDL_WINDOW_ALLOW_HIGHDPI);
    if (!win) {
        printf("Error creating window: %s\n", SDL_GetError());
        return NULL;
    }
    return win;
}

SDL_Renderer* create_renderer(SDL_Window *win) {
    // Create an SDL renderer

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!ren) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return NULL;
    }
    return ren;
}

void toggle_fullscren(SDL_Window *win, SDL_Renderer *ren) {
    uint32_t flags = SDL_GetWindowFlags(win);

    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
        // currently in fullscreen mode => set to windowed
        SDL_SetWindowFullscreen(win, 0);
        SDL_SetWindowSize(win, SCREEN_WIDTH, SCREEN_HEIGHT);
        // Reset logical size to windowed mode size
        SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

    } else {
        // currently windowed => set to fullscreen
        SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
        // Keep the logical size the same as the windowed mode resolution so that
        // the content scales properly in fullscreen mode
        SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

    }
}

int return_with_delay(int valueToReturn) {
    SDL_Delay(100);  // Small safety delay to give time for SDL resources to close
    return valueToReturn;
}

// Determine whether the program is running in CI/CD or not
int isRunningInCI() {
    return (getenv("CI") != NULL);
}

// Handle CI/CD timeout
void check_timeout(float current_time, int *quit) {
    if (current_time >= GAME_TIMEOUT_SECONDS) {
        printf("Game succesfully timed out after %d seconds.\n", GAME_TIMEOUT_SECONDS);
        *quit = 1;
    }
    return;
}