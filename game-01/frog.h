#ifndef FROG_H
#define FROG_H

#include "canvas.h"

#include <stdlib.h>

typedef struct {
    Canvas* canvas;
    float x,y;
    float vx,vy;
    int frame;
    int pixelSize;
} Frog;

Frog* FrogNew(float x,float y,float vx,float vy,int pixelSize);
void FrogDraw(Frog* frog);

#endif
