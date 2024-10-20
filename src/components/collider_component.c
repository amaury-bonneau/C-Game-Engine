#include <SDL.h>

#include "../components/collider_component.h"

int check_collisions(Collider *a, Collider *b) {
    if (a == NULL || b == NULL) {
        printf("Error: One or both collider pointers are NULL\n");
        return 0;  // No collision if invalid collider
    }

    return SDL_HasIntersection(&a->rect, &b->rect);
}
