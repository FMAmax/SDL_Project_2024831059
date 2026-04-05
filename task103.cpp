#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 540;

// game state for both circle
struct GameState{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    //circle 1 moving
    float c1X=0, c1Y=SCREEN_HEIGHT/2, c1R=40;
    float c1Speed = 2.0f;

    //circle 2 controlling
    float c2X = SCREEN_WIDTH/2, c2Y=0, c2R = 40, c2Speed = 8.0f;

    bool is_running= true;
    bool is_colliding = false;

    

};

// prototypes
bool init_game(GameState& state);
void handle_events(GameState& state);
void update_game(GameState& state);
void render_game(GameState& state);
void draw_circle(SDL_Renderer* renderer, float cX,float cY,float r);
void cleanup(GameState& state);

int main(int argc, char* argv[]){
    GameState state;
    if(!init_game(state))
    return -1;

    while(state.is_running){
        handle_events(state);
        update_game(state);
        render_game(state);
        SDL_Delay(16);          // 1000ms/60=16ms
    }
    cleanup(state);
    return 0;
}

bool init_game(GameState& state){
    if(!SDL_Init(SDL_INIT_VIDEO)){
    SDL_Log("SDL_Init Error: %s",SDL_GetError());
    return false;
    }
    if (!SDL_CreateWindowAndRenderer("Task 103: Collision Detection", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &state.window, &state.renderer)) {
    SDL_Log("Window/Renderer Error: %s", SDL_GetError());
    return false;
    }
    return true;

}
void handle_events(GameState& state){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type== SDL_EVENT_QUIT)
        state.is_running = false;

        if(event.type == SDL_EVENT_KEY_DOWN){
            switch(event.key.key){
                case SDLK_UP:
                state.c2Y -= state.c2Speed;
                break;
                case SDLK_DOWN:  
                state.c2Y += state.c2Speed;
                break;
                case SDLK_LEFT:  
                state.c2X -= state.c2Speed; 
                break;
                case SDLK_RIGHT: 
                state.c2X += state.c2Speed; 
                break;
            }
        }
    }
}
void update_game(GameState& state){
    //mvoing circle 1
    state.c1X += state.c1Speed;
     
    //reseting circle position
    if(state.c1X - state.c1R>SCREEN_WIDTH)
    state.c1X = -state.c1R;

    //collision detection logic
    float dx = state.c2X - state.c1X;
    float dy = state.c2Y - state.c1Y;
    float distanceSquared = (dx*dx) + (dy*dy);
    float radsum= state.c1R+ state.c2R;

    if(distanceSquared <= radsum*radsum){
        state.is_colliding= true;
    }
    else{ 
        state.is_colliding = false;
    }
}
void render_game(GameState& state){
    SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
    SDL_RenderClear(state.renderer);

    //showing colour if circles hit
    if(state.is_colliding){
    SDL_SetRenderDrawColor(state.renderer,50,50,255,255);
    }
    else
    SDL_SetRenderDrawColor(state.renderer,50,255,50,255);

    //rendering moving circle
    draw_circle(state.renderer , state.c1X,state.c1Y, state.c1R );
    //redering controlling circle
    draw_circle(state.renderer, state.c2X, state.c2Y, state.c2R);

    SDL_RenderPresent(state.renderer);

}
void draw_circle(SDL_Renderer* renderer, float cX,float cY,float r){
    float maxX = cX + r, minX = cX - r;
    float maxY = cY + r, minY = cY - r;
    for(float x = minX;x<=maxX;x++){
        for(float y= minY;y<=maxY;y++){
            float dx = x - cX;
            float dy = y - cY;
            if ((dx * dx) + (dy * dy) <= (r * r)) {
                SDL_RenderPoint(renderer, x, y);
        }
    }
  }
    
}
void cleanup(GameState& state){
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}