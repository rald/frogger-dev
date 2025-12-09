#include "gl2d.h"
#include "canvas.h"
#include "frog.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PIXEL_SIZE 2
#define SCREEN_WIDTH 160 * PIXEL_SIZE
#define SCREEN_HEIGHT 144 * PIXEL_SIZE

extern gl2dRGBA palette[];

GLFWwindow* window = NULL;
Frog* frog = NULL;

bool isKeyUpPressed = false;
bool isKeyDownPressed = false;
bool isKeyLeftPressed = false;
bool isKeyRightPressed = false;

void update(float dt) {

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)     isKeyUpPressed=false;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)   isKeyDownPressed=false;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)   isKeyLeftPressed=false;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)  isKeyRightPressed=false;

    if(isKeyUpPressed || isKeyDownPressed || isKeyLeftPressed || isKeyRightPressed) return;

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)       isKeyUpPressed=true;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)     isKeyDownPressed=true;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)     isKeyLeftPressed=true;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)    isKeyRightPressed=true;

    if(isKeyUpPressed)      frog->y-=frog->vy;
    if(isKeyDownPressed)    frog->y+=frog->vy;
    if(isKeyLeftPressed)    frog->x-=frog->vx;
    if(isKeyRightPressed)   frog->x+=frog->vx;
}

void render() {
    gl2dSetColor(palette[0]);
    gl2dFillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    
    FrogDraw(frog);
}

int main(void) {

    window = gl2dInit(SCREEN_WIDTH, SCREEN_HEIGHT, "Frogger");
    if (!window) return -1;

    frog = FrogNew((SCREEN_WIDTH-8*2)/2,SCREEN_HEIGHT-8*2,8*2,8*2,2);

    gl2dRunLoopAnim(window, update, render);
    gl2dCleanup(window);

    return 0;
}

