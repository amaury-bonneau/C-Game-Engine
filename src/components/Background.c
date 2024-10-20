#include <SDL.h>
#include "../components/background.h"

#include "../managers/resource_manager.h"

Background init_background(SDL_Renderer *ren,
                            ResourceManager *resource_manager) {
    Background background;
    background.texture =  get_texture(resource_manager, "background");

    if (!background.texture) {
        printf("Failed to load background texture or fallback texture\n");
    }
    return background;
}

void render_background(SDL_Renderer* ren, Background *background) {
    if (background && background->texture) {
        SDL_RenderCopy(ren, background->texture, NULL, NULL);
    }
}

void free_background(Background *background) {
    // if (background && background->texture) {
    //     SDL_DestroyTexture(background->texture);
    //     background->texture = NULL;
    // }
    return;
}
