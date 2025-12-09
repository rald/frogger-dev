#include "gl2d.h"

#define PI 3.14159265359f

gl2dRGBA palette[] = {
    {   8,  24,  32, 255 },
    {  52, 104,  86, 255 },
    { 136, 192, 112, 255 },
    { 224, 248, 208, 255 },
};

GLFWwindow* gl2dInit(int width, int height, const char* title) {
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

// New implementation in gl2d.c
void gl2dRunLoopAnim(GLFWwindow* window, gl2dUpdateCB update_cb, gl2dRenderCB render_cb) {
    double prev_time = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double curr_time = glfwGetTime();
        float dt = (float)(curr_time - prev_time);
        prev_time = curr_time;
 
        // ESC exit
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        
        gl2dClear();
        if (update_cb) update_cb(dt);
        if (render_cb) render_cb();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void gl2dCleanup(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void gl2dClear(void) {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl2dColor(int r, int g, int b) {
    glColor3ub(r, g, b);
}

void gl2dSetColor(gl2dRGBA color) {
    gl2dColor( color.r, color.g, color.b );
}

void gl2dSetPixel(int x,int y,int size) {
    gl2dFillRect(x,y,size,size);
}

void gl2dDrawPoint(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void gl2dDrawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void gl2dDrawRect(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void gl2dFillRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void gl2dDrawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void gl2dFillCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void gl2dDrawPoly(float* verts, int count) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < count * 2; i += 2) {
        glVertex2f(verts[i], verts[i + 1]);
    }
    glEnd();
}

void gl2dFillPoly(float* verts, int count) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < count * 2; i += 2) {
        glVertex2f(verts[i], verts[i + 1]);
    }
    glEnd();
}



int gl2dRectRect(gl2dRect a, gl2dRect b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

int gl2dRectCircle(gl2dRect rect, gl2dCircle circ) {
    float dx = circ.x - (rect.x + rect.w * 0.5f);
    float dy = circ.y - (rect.y + rect.h * 0.5f);
    float rect_cx = rect.w * 0.5f, rect_cy = rect.h * 0.5f;
    float closest_x = fmaxf(rect.x, fminf(circ.x, rect.x + rect.w));
    float closest_y = fmaxf(rect.y, fminf(circ.y, rect.y + rect.h));
    float dist_x = circ.x - closest_x;
    float dist_y = circ.y - closest_y;
    return (dist_x * dist_x + dist_y * dist_y) <= (circ.r * circ.r);
}

int gl2dCircleCircle(gl2dCircle a, gl2dCircle b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dist = sqrtf(dx*dx + dy*dy);
    return dist <= (a.r + b.r);
}

