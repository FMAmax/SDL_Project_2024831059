#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 520;
const float INITIAL_RADIUS = 10.0f;
const float GROWTH_RATE = 1.0f;

// variables structure 
struct GameState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool is_running = true;

    float cX = SCREEN_WIDTH / 2.0f;
    float cY = SCREEN_HEIGHT / 2.0f;
    float radius = INITIAL_RADIUS;
};

//prototypes
bool init_game(GameState& state);
void handle_events(GameState& state);
void update_game(GameState& state);
void render_game(GameState& state);
void draw_circle(SDL_Renderer* renderer, float cX, float cY, float r);
void cleanup(GameState& state);

int main(int argc, char* argv[]) {
    GameState state;

    if (!init_game(state)) {
        return -1;
    }

    // Gameloop
    while (state.is_running) {
        handle_events(state); 
        update_game(state);   
        render_game(state);   
    }
    cleanup(state);
    return 0;
}

bool init_game(GameState& state) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Task 102: Growing Circle", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &state.window, &state.renderer)) {
        SDL_Log("Window/Renderer Error: %s", SDL_GetError());
        return false;
    }

    return true;
}

void handle_events(GameState& state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            state.is_running = false;
        }
    }
}

void update_game(GameState& state) {

    state.radius += GROWTH_RATE;        //radius increase ovr time

    //collision detection
    bool hit_horizontal = (state.cX + state.radius >= SCREEN_WIDTH) || (state.cX - state.radius <= 0); 
    bool hit_vertical   = (state.cY + state.radius >= SCREEN_HEIGHT) || (state.cY - state.radius <= 0);

    if (hit_horizontal || hit_vertical) {
        state.radius = INITIAL_RADIUS; // reset circle radius
    }
}

void render_game(GameState& state) {
    // clear render
    SDL_SetRenderDrawColor(state.renderer,0,0,0,255); // black background
    SDL_RenderClear(state.renderer);

    
    SDL_SetRenderDrawColor(state.renderer,225,100,0,255); // circle colour orangish
    draw_circle(state.renderer, state.cX, state.cY, state.radius);

    //render circle
    SDL_RenderPresent(state.renderer);
}

void draw_circle(SDL_Renderer* renderer, float cX, float cY, float r) {
    //rendering circle
    float minX = cX - r;
    float maxX = cX + r;
    float minY = cY - r;
    float maxY = cY + r;

    for (float x = minX; x <= maxX; x++) {
        for (float y = minY; y <= maxY; y++) {
            if (( x-cX )*( x-cX ) + ( y-cY )*( y-cY ) - r*r <= 0) {
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}

void cleanup(GameState& state) {
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}