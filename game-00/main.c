#include "glprims.h"
#include <stdio.h>

void render(void) {
    // Filled red rectangle
    glprims_color(1.0f, 0.0f, 0.0f);
    glprims_fill_rect(50, 50, 100, 80);

    // Red rectangle outline
    glprims_color(0.8f, 0.2f, 0.2f);
    glprims_draw_rect(50, 50, 100, 80);

    // Green filled circle
    glprims_color(0.0f, 1.0f, 0.0f);
    glprims_fill_circle(200, 100, 40, 32);

    // Green circle outline
    glprims_color(0.2f, 0.8f, 0.2f);
    glprims_draw_circle(200, 100, 40, 32);

    // Blue line
    glprims_color(0.0f, 0.0f, 1.0f);
    glprims_draw_line(350, 50, 450, 150);

    // Points
    glprims_color(1.0f, 1.0f, 0.0f);
    glprims_draw_point(400, 100);
    glprims_draw_point(420, 120);

    // Pentagon (5 vertices)
    float pentagon[] = {500, 60, 580, 80, 610, 140, 580, 200, 500, 220};
    glprims_color(1.0f, 0.5f, 0.0f);
    glprims_fill_poly(pentagon, 5);
    
    glprims_color(0.7f, 0.3f, 0.0f);
    glprims_draw_poly(pentagon, 5);
}

int main(void) {
    GLFWwindow* window = glprims_init(800, 600, "OpenGL 1.1 Primitives");
    if (!window) return -1;

    glprims_run_loop(window, render);
    glprims_cleanup(window);
    return 0;
}

