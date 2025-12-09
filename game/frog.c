#include "frog.h"

extern GLFWwindow *window;

static float epsilon=0.0001;

static int sgn(int n) {
    return n<0?-1:n>0?1:0;
}

Frog* FrogNew(float x,float y,float vx,float vy,float speed,int pixelSize) {
    Frog* frog=malloc(sizeof(*frog));
    frog->canvas=CanvasLoad("frog.cvs");
    frog->x=x;
    frog->y=y;
    frog->vx=vx;
    frog->vy=vy;
    frog->speed=speed;
    frog->pixelSize=pixelSize;
    frog->w=frog->canvas->w;
    frog->h=frog->canvas->h;
    frog->frame=0;
    frog->canJump=true;
    frog->state=FROG_STATE_IDLE;
    frog->direction=FROG_DIRECTION_UP;
}

void FrogFree(Frog** frog) {
    CanvasFree(&(*frog)->canvas);
    free(*frog);
    (*frog)=NULL;
}

void FrogDraw(Frog* frog) {
    switch(frog->state) {
    case FROG_STATE_IDLE:
        switch(frog->direction) {
            case FROG_DIRECTION_UP:
                CanvasDraw(frog->canvas,frog->x,frog->y,0,frog->pixelSize);
                break;
            case FROG_DIRECTION_RIGHT:
                CanvasDraw(frog->canvas,frog->x,frog->y,1,frog->pixelSize);
                break;
            case FROG_DIRECTION_DOWN:
                CanvasDraw(frog->canvas,frog->x,frog->y,2,frog->pixelSize);
                break;
            case FROG_DIRECTION_LEFT:
                CanvasDraw(frog->canvas,frog->x,frog->y,3,frog->pixelSize);
                break;
        }
        break;
    case FROG_STATE_JUMPING:
        switch(frog->direction) {
            case FROG_DIRECTION_UP:
                CanvasDraw(frog->canvas,frog->x,frog->y,4,frog->pixelSize);
                break;
            case FROG_DIRECTION_RIGHT:
                CanvasDraw(frog->canvas,frog->x,frog->y,5,frog->pixelSize);
                break;
            case FROG_DIRECTION_DOWN:
                CanvasDraw(frog->canvas,frog->x,frog->y,6,frog->pixelSize);
                break;
            case FROG_DIRECTION_LEFT:
                CanvasDraw(frog->canvas,frog->x,frog->y,7,frog->pixelSize);
                break;
        }
        break;
    }
}

void FrogUpdate(Frog* frog,float dt) {
    switch(frog->state) {
    case FROG_STATE_IDLE:
        FrogUpdateIdle(frog,dt);
        break;
    case FROG_STATE_JUMPING:
        FrogUpdateJumping(frog,dt);
        break;
    }
}

void FrogUpdateIdle(Frog* frog,float dt) {
    static bool isLeftKeyPressed = false;
    static bool isRightKeyPressed = false;
    static bool isDownKeyPressed = false;
    static bool isUpKeyPressed = false;
    
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)     isLeftKeyPressed = true;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)    isRightKeyPressed = true;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)     isDownKeyPressed = true;
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)       isUpKeyPressed = true;

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)     isLeftKeyPressed = false;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)    isRightKeyPressed = false;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)     isDownKeyPressed = false;
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)       isUpKeyPressed = false;
        
    frog->vx=0;
    frog->vy=0;

    if(frog->canJump) {
    
        if(isLeftKeyPressed) {
            if(frog->direction==FROG_DIRECTION_LEFT) {        
                frog->vx = -frog->speed;
                frog->state = FROG_STATE_JUMPING;
            } else {
                frog->direction=FROG_DIRECTION_LEFT;
            }
            frog->canJump=false;
        }
        
        if(isRightKeyPressed) {
            if(frog->direction==FROG_DIRECTION_RIGHT) {
                frog->vx = frog->speed;    
                frog->state = FROG_STATE_JUMPING;
            } else {
                frog->direction = FROG_DIRECTION_RIGHT;
            }
            frog->canJump=false;
        }
        
        if(isUpKeyPressed) {
            if(frog->direction==FROG_DIRECTION_UP) {
                frog->vy = -frog->speed;    
                frog->state = FROG_STATE_JUMPING;
            } else {
                frog->direction = FROG_DIRECTION_UP;
            }
            frog->canJump=false;
        }
        
        if(isDownKeyPressed) {
            if(frog->direction==FROG_DIRECTION_DOWN) {
                frog->vy = frog->speed;    
                frog->state = FROG_STATE_JUMPING;
            } else {
                frog->direction = FROG_DIRECTION_DOWN;
            }
            frog->canJump=false;
        }  
        
    } else if(!(isLeftKeyPressed || isRightKeyPressed || isDownKeyPressed || isUpKeyPressed)) {
        frog->canJump = true;
    }
  
}

void FrogUpdateJumping(Frog* frog,float dt) {
    frog->x+=sgn(frog->vx);
    frog->y+=sgn(frog->vy);
    
    if(frog->x<0) frog->x=0;
    if(frog->y<0) frog->y=0;
    if(frog->x>SCREEN_WIDTH-8*PIXEL_SIZE) frog->x=SCREEN_WIDTH-8*PIXEL_SIZE;
    if(frog->y>SCREEN_HEIGHT-8*PIXEL_SIZE) frog->y=SCREEN_HEIGHT-8*PIXEL_SIZE;    

    frog->vx-=sgn(frog->vx);
    frog->vy-=sgn(frog->vy);
    
    if(fabs(frog->vx)<=epsilon && fabs(frog->vy)<=epsilon) {
        frog->vx=0;
        frog->vy=0;
        frog->state=FROG_STATE_IDLE;
    }        
}

