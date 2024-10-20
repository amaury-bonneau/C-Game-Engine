#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include "components/player.h"
#include "components/entity.h"
#include "components/background.h"

#include "managers/resource_manager.h"

SDL_Window* create_window();
SDL_Renderer* create_renderer();
int main(int argc, char *argv[]);
void handle_input(SDL_Event e, Player *player, int *quit, SDL_Window *win, SDL_Renderer *ren);
void update(Player* player, Entity *entities[], int entity_count, float delta_time);
void terminate_program(Background *background, Player *player, Entity *entities[], int *entity_count, SDL_Renderer *ren, SDL_Window *win, ResourceManager *resource_manager);
void render_textures(SDL_Renderer *ren, Background *background, Player *player, Entity *entities[]);
void toggle_fullscren(SDL_Window *win, SDL_Renderer *ren);
int return_with_delay(int valueToReturn);
void check_timeout(float current_time, int is_ci, int *quit);

#endif