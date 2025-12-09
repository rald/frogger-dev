#include "common.h"
#include "gl2d.h"
#include "frog.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

extern gl2dRGBA palette[];

GLFWwindow* window = NULL;
Frog* frog = NULL;
int frame=0;

void update(float dt) {
    frame++;
    FrogUpdate(frog,dt);
}

void render() {
    gl2dSetColor(palette[0]);
    gl2dFillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    
    FrogDraw(frog);
}

int main(void) {

    window = gl2dInit(SCREEN_WIDTH, SCREEN_HEIGHT, "Frogger");
    if (!window) return -1;

    frog = FrogNew((SCREEN_WIDTH-8*PIXEL_SIZE)/2,SCREEN_HEIGHT-8*PIXEL_SIZE,8*PIXEL_SIZE,8*PIXEL_SIZE,8*PIXEL_SIZE,PIXEL_SIZE);

    gl2dRunLoopAnim(window, update, render);

    FrogFree(&frog);

    gl2dCleanup(window);

    return 0;
}

