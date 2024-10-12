#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "player.h"
#include "collider.h"
#include "config.h"
#include "texture.h"

#include "jsonManager.h"
#include "resourceManager.h"

Player* init_player(SDL_Renderer *ren,
                    ResourceManager *resourceManager,
                    int speed,
                    int velX,
                    int velY) {
    Player *player = malloc(sizeof(Player));  // Allocate memory for Player

    player->speed = speed;
    player->velX = velX;
    player->velY = velY;

    player->rect.h = CHARACTER_HEIGHT;
    player->rect.w = CHARACTER_WIDTH;
    player->rect.x = CHARACTER_STARTING_X;
    player->rect.y = CHARACTER_STARTING_Y;

    // Loading player texture
    player->texture = get_texture(resourceManager, "player");
    if (!player->texture) {
        printf("Failed to load player texture or fallback texture\n");
    }

    player->posAccumulator.x = SCREEN_WIDTH / 2.0f;
    player->posAccumulator.y = SCREEN_HEIGHT / 2.0f;
    
    player->collider.rect = player->rect;
    player->collider.isCircle = 0;
    player->collider.radius = 0;

    return player;
}

void update_player(Player *player, float deltaTime){
    player->posAccumulator.x += player->velX * deltaTime;
    player->posAccumulator.y += player->velY * deltaTime;
    // printf("Player position: (%f, %f)\n", player->posAccumulator.x, player->posAccumulator.y);

}

void render_player(SDL_Renderer* ren, Player *player) {
        player->rect.x = (int)(player->posAccumulator.x);
        player->rect.y = (int)(player->posAccumulator.y);

        SDL_RenderCopy(ren, player->texture, NULL, &player->rect);
}

void free_player(Player *player){
    if (player) {
        printf("Player is not NULL, freeing...\n");
        free(player);
        printf("Player freed successfully.\n");
    } else {
        printf("Player is NULL, nothing to free.\n");
    }
    return;
}
