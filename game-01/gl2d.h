#ifndef GL2D_H
#define GL2D_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <math.h>
#include <stdio.h>

typedef struct {
    int r,g,b,a;
} gl2dRGBA;

// Initialize GLFW window and OpenGL 1.1 context
GLFWwindow* gl2dInit(int width, int height, const char* title);

// Updated header in gl2d.h
typedef void (*gl2dUpdateCB)(float dt);
typedef void (*gl2dRenderCB)();
void gl2dRunLoopAnim(GLFWwindow* window, gl2dUpdateCB update_cb, gl2dRenderCB render_cb);

// Cleanup
void gl2dCleanup(GLFWwindow* window);

// Core functions
void gl2dClear(void);
void gl2dColor(int r, int g, int b);
void gl2dSetColor(gl2dRGBA color);

// Drawing primitives (outline)
void gl2dSetPixel(int x,int y,int size);
void gl2dDrawPoint(float x, float y);
void gl2dDrawLine(float x1, float y1, float x2, float y2);
void gl2dDrawRect(float x, float y, float w, float h);
void gl2dDrawCircle(float x, float y, float radius, int segments);
void gl2dDrawPoly(float* verts, int count);

// Filled primitives
void gl2dFillRect(float x, float y, float w, float h);
void gl2dFillCircle(float x, float y, float radius, int segments);
void gl2dFillPoly(float* verts, int count);

// Collision detection (AABB + Circle)
typedef struct {
    float x, y, w, h;
} gl2dRect;

typedef struct {
    float x, y, r;
} gl2dCircle;

int gl2dRectRect(gl2dRect a, gl2dRect b);
int gl2dRectCircle(gl2dRect rect, gl2dCircle circ);
int gl2dCircleCircle(gl2dCircle a, gl2dCircle b);

#endif

