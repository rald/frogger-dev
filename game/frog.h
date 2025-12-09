#ifndef FROG_H
#define FROG_H

#include "common.h"
#include "canvas.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
    FROG_STATE_IDLE = 0,
    FROG_STATE_JUMPING,  
} FrogState;

typedef enum {
    FROG_DIRECTION_UP = 0,
    FROG_DIRECTION_RIGHT,
    FROG_DIRECTION_DOWN,
    FROG_DIRECTION_LEFT,
} FrogDirection;

typedef struct {
    Canvas* canvas;
    float x,y;
    float vx,vy;
    float speed;
    int frame;
    int pixelSize;
    int w,h;
    bool canJump;
    FrogState state;
    FrogDirection direction;
} Frog;

Frog* FrogNew(float x,float y,float vx,float vy,float speed,int pixelSize);
void FrogFree(Frog** frog);

void FrogDraw(Frog* frog);

void FrogUpdate(Frog* frog,float dt);
void FrogUpdateIdle(Frog* frog,float dt);
void FrogUpdateJumping(Frog* frog,float dt);

#endif

