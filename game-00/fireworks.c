#include "glprims.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_PARTICLES 1000
#define MAX_FIREWORKS 5
#define SCREEN_HEIGHT 600

typedef struct {
    float x, y;
    float vx, vy;
    float life;
    float max_life;
    float size;
    int active;
    float r, g, b;
} Particle;

typedef struct {
    float x, y;
    float vy;
    int exploding;
    float explode_time;
    int active;
} Firework;

Particle particles[MAX_PARTICLES];
Firework fireworks[MAX_FIREWORKS];
float time_step = 0.016f;  // ~60 FPS
int score = 0;
float global_time = 0;

void init_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].active = 0;
    }
}

void init_fireworks() {
    for (int i = 0; i < MAX_FIREWORKS; i++) {
        fireworks[i].active = 0;
    }
}

int spawn_particle(float x, float y, float speed, float life, float r, float g, float b) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].vx = (rand() % 200 - 100) / 100.0f * speed;
            particles[i].vy = (rand() % 200 - 100) / 100.0f * speed * -1.0f;  // Upward bias
            particles[i].life = life;
            particles[i].max_life = life;
            particles[i].size = 1.5f + (rand() % 8) / 10.0f;
            particles[i].active = 1;
            particles[i].r = r;
            particles[i].g = g;
            particles[i].b = b;
            return 1;
        }
    }
    return 0;
}

void spawn_firework() {
    for (int i = 0; i < MAX_FIREWORKS; i++) {
        if (!fireworks[i].active) {
            fireworks[i].x = 50.0f + (rand() % 700);  // Bottom span
            fireworks[i].y = SCREEN_HEIGHT - 20;       // Bottom of screen
            fireworks[i].vy = 2.2f + (rand() % 80) / 100.0f;  // Strong upward velocity
            fireworks[i].active = 1;
            fireworks[i].exploding = 0;
            fireworks[i].explode_time = 0;
            return;
        }
    }
}

void update_fireworks() {
    for (int i = 0; i < MAX_FIREWORKS; i++) {
        if (fireworks[i].active) {
            if (!fireworks[i].exploding) {
                // Rise from bottom to top (y decreases upward)
                fireworks[i].y -= fireworks[i].vy * time_step * 60;  // Negative = upward
                fireworks[i].vy -= 0.08f * time_step * 60;           // Gravity pulls down
                
                // Explode near top of screen
                if (fireworks[i].y < 150 || fireworks[i].vy < 0.1f) {
                    fireworks[i].exploding = 1;
                    fireworks[i].explode_time = 0;
                }
            } else {
                fireworks[i].explode_time += time_step;
                if (fireworks[i].explode_time > 0.4f) {
                    fireworks[i].active = 0;
                }
            }
        }
    }
}

void update_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].x += particles[i].vx * time_step * 60;
            particles[i].y += particles[i].vy * time_step * 60;  // vy negative = upward spread
            particles[i].vx *= 0.97f;  // Air resistance
            particles[i].vy *= 0.97f;
            particles[i].vy += 0.25f * time_step * 60;  // Gravity pulls down
            particles[i].life -= time_step;
            
            if (particles[i].life <= 0 || particles[i].y > SCREEN_HEIGHT || particles[i].x < 0 || particles[i].x > 800) {
                particles[i].active = 0;
            }
        }
    }
}

void explode(float x, float y) {
    static const char* colors[] = {
        "1.0 0.2 0.2", "0.2 1.0 0.2", "0.2 0.2 1.0", 
        "1.0 1.0 0.2", "1.0 0.2 1.0", "0.2 1.0 1.0",
        "1.0 0.5 0.0", "0.5 1.0 0.0"
    };
    int color_idx = rand() % 8;
    float r = 1.0f, g = 1.0f, b = 1.0f;
    sscanf(colors[color_idx], "%f %f %f", &r, &g, &b);
    
    int particle_count = 60 + (rand() % 40);
    for (int i = 0; i < particle_count; i++) {
        float angle = (rand() % 360) * M_PI / 180.0f;
        float speed = 3.0f + (rand() % 300) / 100.0f;
        spawn_particle(x, y, speed, 1.0f + (rand() % 50)/100.0f, r, g, b);
    }
    score += 150;
}

void render(void) {
    global_time += time_step;
    glprims_clear();
    
    update_particles();
    update_fireworks();
    
    // Spawn fireworks from bottom every ~1-2 seconds
    if ((int)(global_time * 10) % 15 == 0 && rand() % 3 == 0) {
        spawn_firework();
    }
    
    // Trigger explosions
    for (int i = 0; i < MAX_FIREWORKS; i++) {
        if (fireworks[i].active && fireworks[i].exploding && 
            fireworks[i].explode_time < 0.03f) {
            explode(fireworks[i].x, fireworks[i].y);
        }
    }
    
    // Draw firework rockets (bright trails)
    for (int i = 0; i < MAX_FIREWORKS; i++) {
        if (fireworks[i].active && !fireworks[i].exploding) {
            glprims_color(1.0f, 1.0f, 0.7f);
            glprims_fill_circle(fireworks[i].x, fireworks[i].y, 4, 16);
            glprims_color(1.0f, 0.8f, 0.0f);
            glprims_draw_circle(fireworks[i].x, fireworks[i].y, 4, 16);
        }
    }
    
    // Draw fading particles
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            float alpha = particles[i].life / particles[i].max_life;
            glprims_color4(particles[i].r, particles[i].g, particles[i].b, alpha * 0.8f);
            glprims_fill_circle(particles[i].x, particles[i].y, 
                              particles[i].size * alpha + 0.8f, 12);
        }
    }
    
    // Simple score bars
    glprims_color(1.0f, 1.0f, 1.0f);
    char score_str[20];
    sprintf(score_str, "SCORE: %d", score);
    for (int i = 0; score_str[i]; i++) {
        glprims_fill_rect(10 + i * 20, 10, 15, 20);
    }
}

int main(void) {
    srand(time(NULL));
    init_particles();
    init_fireworks();
    
    GLFWwindow* window = glprims_init(800, 600, "Fireworks");
    if (!window) return -1;
    
    glprims_run_loop(window, render);
    glprims_cleanup(window);
    printf("Final Score: %d\n", score);
    return 0;
}

