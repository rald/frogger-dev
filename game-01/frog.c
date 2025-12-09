#include "frog.h"

Frog* FrogNew(float x,float y,float vx,float vy,int pixelSize) {
    Frog* frog=malloc(sizeof(*frog));
    frog->canvas=CanvasLoad("frog.cvs");
    frog->x=x;
    frog->y=y;
    frog->vx=vx;
    frog->vy=vy;
    frog->pixelSize=pixelSize;
}

void FrogDraw(Frog* frog) {
    CanvasDraw(frog->canvas,frog->x,frog->y,frog->frame,frog->pixelSize);
}

