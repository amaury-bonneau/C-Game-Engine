#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "main.h"
#include "player.h"
#include "texture.h"
#include "config.h"
#include "entity.h"
#include "collider.h"
#include "background.h"
#include "resourceManager.h"

#define MAX_ENTITIES 100

int main(int argc, char *argv[]) {

    SDL_Window* win = NULL;
    SDL_Renderer* ren = NULL;
    ResourceManager* resourceManager = NULL;

    Player* player = NULL;
    Background background;

    // Entity storing
    Entity* entities[MAX_ENTITIES];
    int entityCount = 0;

    win = create_window();
    if (!win) {
        terminate_program(&background, player, entities, &entityCount, ren, win, resourceManager);
        return_with_delay(1);
    }
    ren = create_renderer(win);
    if (!ren) {
        terminate_program(&background, player, entities, &entityCount, ren, win, resourceManager);
        return_with_delay(1);
    }
    // Set logical size for initial window size
    SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize resourceManager
    resourceManager = load_resources(ren);

    // Initialize Background
    background = init_background(ren, resourceManager);

    // Initialize Player
    int speed = 200;
    int velX = 0, velY = 0;
    player = init_player(ren, resourceManager, speed, velX, velY);

    float deltaTime = 0;
    float lastTime = SDL_GetTicks() / 1000.0f; // initializing lastTime right at start so deltaTime has a meaningful value
    
    // Initialize entities
    Entity *obstacle = init_entity(ren, resourceManager, speed, velX, velY);
    if (obstacle == NULL) {
        printf("Failed to initialize entity\n");
        terminate_program(&background, player, entities, &entityCount, ren, win, resourceManager);
        return_with_delay(1);  // Exit early if entity creation failed
    }
    if (entityCount < MAX_ENTITIES) {
        entities[entityCount++] = obstacle;
    } else {
        printf("Error: max number of entities attained.");
    }

    // Main loop flag
    int quit = 0;
    SDL_Event e;

    // Main loop
    while (!quit) {
        float currentTime = SDL_GetTicks() / 1000.0f; // The number of seconds elapsed since init of SDL lib at start of the program
        deltaTime = currentTime - lastTime; // The delta between current frame time and previous frame time
        if (deltaTime > 0.1f) deltaTime = 0.1f;  // Cap deltaTime at 0.1 seconds to avoid problematic enormous or minuscule values
        lastTime = currentTime;

        // Handle input
        handle_input(e, player, &quit, win, ren);

        // Update logic (player position, etc.)
        update(player, entities, entityCount, deltaTime);

        // Check for collisions
        for (size_t i = 0; i < entityCount; i++)
        {
            // if (check_collisions(&player.collider, &entities[i]->collider)) {
            //     printf("collision détectée");
            // }
        }

        // Render everything
        render_textures(ren, &background, player, entities);

    }

    terminate_program(&background, player, entities, &entityCount, ren, win, resourceManager);
    return_with_delay(100);
}

void update(Player *player, Entity *entities[], int entityCount, float deltaTime) {
    update_player(player, deltaTime);
    // update_entities(entities, deltaTime, entityCount);
}

void terminate_program(Background *background, Player *player, Entity *entities[], int *entityCount, SDL_Renderer *ren, SDL_Window *win, ResourceManager *resourceManager) {
    printf("Terminating program...\n");

    if (resourceManager) {
        printf("Unloading resources...\n");
        unload_resources(resourceManager);
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
        free_entities(entities, entityCount);
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
            entities[0]->rect.x = (int)(entities[0]->posAccumulator.x);
            entities[0]->rect.y = (int)(entities[0]->posAccumulator.y);
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