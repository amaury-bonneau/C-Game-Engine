#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "../components/player.h"
#include "../components/collider_component.h"

#include "../config.h"

#include "../managers/resource_manager.h"
#include "../managers/memory_manager.h"

Player* init_player(SDL_Renderer *ren,
                    ResourceManager *resource_manager,
                    int speed,
                    int velX,
                    int velY) {
    Player *player = (Player*)allocateMemory(sizeof(Player));  // Allocate memory for Player

    player->speed = speed;
    player->velX = velX;
    player->velY = velY;

    player->rect.h = CHARACTER_HEIGHT;
    player->rect.w = CHARACTER_WIDTH;
    player->rect.x = CHARACTER_STARTING_X;
    player->rect.y = CHARACTER_STARTING_Y;

    // Loading player texture
    player->texture = get_texture(resource_manager, "player");
    if (!player->texture) {
        printf("Failed to load player texture or fallback texture\n");
    }

    player->position_accumulator.x = SCREEN_WIDTH / 2.0f;
    player->position_accumulator.y = SCREEN_HEIGHT / 2.0f;
    
    player->collider.rect = player->rect;
    player->collider.isCircle = 0;
    player->collider.radius = 0;

    return player;
}

void update_player(Player *player, float delta_time){
    player->position_accumulator.x += player->velX * delta_time;
    player->position_accumulator.y += player->velY * delta_time;
    // printf("Player position: (%f, %f)\n", player->position_accumulator.x, player->position_accumulator.y);

}

void render_player(SDL_Renderer* ren, Player *player) {
        player->rect.x = (int)(player->position_accumulator.x);
        player->rect.y = (int)(player->position_accumulator.y);

        SDL_RenderCopy(ren, player->texture, NULL, &player->rect);
}

void free_player(Player *player){
    if (player) {
        printf("Player is not NULL, freeing...\n");
        freeMemory(player);
        printf("Player freed successfully.\n");
    } else {
        printf("Player is NULL, nothing to free.\n");
    }
    return;
}
