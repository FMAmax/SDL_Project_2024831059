#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> // Required for cross-platform main entry
#include <iostream>

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("Task 101: SDL3 Window", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Render Logic
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // gray background
        SDL_RenderClear(renderer);

        SDL_FRect rect = { 220.0f, 140.0f, 200.0f, 200.0f }; 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}