#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include "player.h"
#include "background.h"
#include "resourceManager.h"
#include "entity.h"

SDL_Window* create_window();
SDL_Renderer* create_renderer();
void handle_input(SDL_Event e, Player *player, int *quit, SDL_Window *win, SDL_Renderer *ren);
void update(Player* player, Entity *entities[], int entityCount, float deltaTime);
void terminate_program(Background *background, Player *player, Entity *entities[], int *entityCount, SDL_Renderer *ren, SDL_Window *win, ResourceManager *resourceManager);
void render_textures(SDL_Renderer *ren, Background *background, Player *player, Entity *entities[]);
void toggle_fullscren(SDL_Window *win, SDL_Renderer *ren);
int return_with_delay(int valueToReturn);

#endif