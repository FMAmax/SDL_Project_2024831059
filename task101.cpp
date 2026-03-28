#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> 
#include <iostream>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 520

void DrawCircle(SDL_Renderer* renderer, float cX, float cY, float radius) {
    float minX = cX - radius;
    float maxX = cX + radius;
    float minY = cY - radius;
    float maxY = cY + radius;

    for (float x = minX; x <= maxX; x++) {
        for (float y = minY; y <= maxY; y++) {
            
            if (( x-cX )*( x-cX ) + ( y-cY )*( y-cY ) - radius*radius <= 0) {
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("Task 101: SDL3 Window", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); 
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 220, 155, 0, 255); 
        
        DrawCircle(renderer, 540.0f, 265.0f, 200.0f);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}