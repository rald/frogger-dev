#ifndef CANVAS_H
#define CANVAS_H

#include "gl2d.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int w,h,frames,transparent;
    int *pixels;
} Canvas;

void CanvasFree(Canvas** canvas);
Canvas* CanvasLoad(char *filename);
void CanvasDraw(Canvas *canvas,int x,int y,int frame,int size);

#endif


