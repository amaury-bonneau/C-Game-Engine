#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

// Collider
typedef struct {
    SDL_Rect rect;
    int isCircle;
    int radius;
} Collider;

int check_collisions(Collider *a, Collider *b);

#ifdef __cplusplus
}
#endif

#endif