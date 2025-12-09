#include "glprims.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265359f

GLFWwindow* glprims_init(int width, int height, const char* title) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    // Request OpenGL 1.1 legacy context (immediate mode compatible)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);  // Legacy mode [web:16][web:19]

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // VSync

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);  // 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void glprims_run_loop(GLFWwindow* window, void (*render_cb)(void)) {
    while (!glfwWindowShouldClose(window)) {
        glprims_clear();
        render_cb();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void glprims_cleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void glprims_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void glprims_color(float r, float g, float b) {
    glColor3f(r, g, b);
}

void glprims_color4(float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
}

void glprims_draw_point(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void glprims_draw_line(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void glprims_draw_rect(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void glprims_fill_rect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void glprims_draw_circle(float x, float y, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void glprims_fill_circle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void glprims_draw_poly(float* verts, int count) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < count * 2; i += 2) {
        glVertex2f(verts[i], verts[i + 1]);
    }
    glEnd();
}

void glprims_fill_poly(float* verts, int count) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < count * 2; i += 2) {
        glVertex2f(verts[i], verts[i + 1]);
    }
    glEnd();
}

