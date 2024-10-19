#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL.h>

// Collider
typedef struct {
    SDL_Rect rect;
    int isCircle;
    int radius;
} Collider;

int check_collisions(Collider *a, Collider *b);

#endif