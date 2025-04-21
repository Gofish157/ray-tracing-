#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>

#define PI 3.14159265
#define HEIGHT 900
#define WIDTH 1500
#define COLOR_WHITE 0xffffffff
static SDL_Window* window;
static SDL_Renderer* renderer;
static float mouse_x = WIDTH/2;
static float mouse_y = HEIGHT/2;



//circle
#define X 450
#define Y 300
#define RADIUS 50.0
static float X_0 = 2*RADIUS;
static float dx = 2;
struct CIRCLE {
    float x;
    float y;
    float r;
};

void fill_circule(struct CIRCLE a) {
    SDL_FRect rect;
    rect.h = 1;
    rect.w = 1;
    for (float i = -a.r; i <= a.r; i+=1) {
        for (float j = -a.r; j <= a.r; j+=1) {
            if (((i)*(i) + (j)*(j)) < a.r*a.r) {
                rect.x = a.x+i;
                rect.y = a.y+j;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

bool object_hit(float x, float y, struct CIRCLE a) {
    if (((a.x - x) * (a.x - x)) + (((a.y - y)) * (a.y - y)) <= a.r*a.r) {
        return true;
    }
    else return false;
}

//rays
#define NUMBER_OF_RAYS 150
struct RAY {
    float x0;
    float y0;
    float corner;
};

void fill_ray(struct RAY a, struct CIRCLE c) {
    SDL_FRect rect;
    rect.h = 1;
    rect.w = 1;
    float dx = cos(a.corner);
    float dy = sin(a.corner);
    float x = a.x0;
    float y = a.y0;
    for (int i = 0; i < 2000; i++) {
        x += dx;
        y += dy;
        if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT || object_hit(x, y, c)) break;
        rect.x = x;
        rect.y = y;
        SDL_RenderFillRect(renderer, &rect);
    }
}






SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("raytraice", WIDTH, HEIGHT, 0, &window, &renderer);
    return SDL_APP_CONTINUE;
}
SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_SetRenderDrawColor(renderer, 30,30, 30, 255);
    SDL_RenderClear(renderer);
    struct CIRCLE c, c_o;
    struct RAY r;
    c_o.r = 2*RADIUS;
    c_o.x = X_0;
    c_o.y = HEIGHT/2;
    c.r = RADIUS;
    c.x = mouse_x;
    c.y = mouse_y;
    r.x0 = c.x;
    r.y0 = c.y;
    SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
    for (float corner = -PI; corner < PI; corner += (2*PI/NUMBER_OF_RAYS)) {
        r.corner = corner;
        fill_ray(r, c_o);
    }
    
    fill_circule(c);
    X_0 += dx;

    if (X_0 + 2*RADIUS > WIDTH || X_0 - 2*RADIUS < 0) dx = - dx;

    X_0 += dx;
    fill_circule(c_o);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_MOUSE_MOTION) {
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
    } 
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {

}
int main(int argc, char *argv[]){
    return SDL_EnterAppMainCallbacks(argc, argv, SDL_AppInit, SDL_AppIterate, SDL_AppEvent, SDL_AppQuit);
}
