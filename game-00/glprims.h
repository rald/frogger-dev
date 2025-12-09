#ifndef GLPRIMS_H
#define GLPRIMS_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>

// Initialize GLFW window and OpenGL 1.1 context
GLFWwindow* glprims_init(int width, int height, const char* title);

// Main render loop handler
void glprims_run_loop(GLFWwindow* window, void (*render_cb)(void));

// Cleanup
void glprims_cleanup(GLFWwindow* window);

// Core functions
void glprims_clear(void);
void glprims_color(float r, float g, float b);
void glprims_color4(float r, float g, float b, float a);

// Drawing primitives (outline)
void glprims_draw_point(float x, float y);
void glprims_draw_line(float x1, float y1, float x2, float y2);
void glprims_draw_rect(float x, float y, float w, float h);
void glprims_draw_circle(float x, float y, float radius, int segments);
void glprims_draw_poly(float* verts, int count);

// Filled primitives
void glprims_fill_rect(float x, float y, float w, float h);
void glprims_fill_circle(float x, float y, float radius, int segments);
void glprims_fill_poly(float* verts, int count);

#endif

