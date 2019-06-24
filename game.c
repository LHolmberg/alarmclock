#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Surface* Backbuffer = NULL;
SDL_Window* Window = NULL;
SDL_Surface* SpriteImage = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600 ;

int score;
int startingSize = 50;
int maxVel = 1.4;
int initVel = 1;

int gameLoop = 1;

SDL_Event event;

int direction;

SDL_Rect food = { 50, 450, 100, 80 };
SDL_Rect snake = {1600 / 2, 900/2, 50,50};


void Input(){

    SDL_PumpEvents();
    Uint8* keystate = SDL_GetKeyboardState(NULL);

    if(keystate[SDL_SCANCODE_D])
        direction = 1;
    
    if(keystate[SDL_SCANCODE_A])
        direction = 2;
    
    if(keystate[SDL_SCANCODE_W])
        direction = 3;
    
    if(keystate[SDL_SCANCODE_S])
        direction = 4;
    
    if(keystate[SDL_SCANCODE_ESCAPE])
        gameLoop = 0;
    
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            gameLoop = 0;
    }
}

void StartingPoint(){
    snake.x = 1600/2;
    snake.y = 900/2;
    score = 0;
}

void Dead(){
    StartingPoint();
    snake.w = startingSize;
}

int main(int argc, char* argcs[])
{
    float x[4];
    Window = SDL_CreateWindow("Game",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1600, 900, SDL_WINDOW_SHOWN);

    SDL_Renderer * renderer = SDL_CreateRenderer(Window, -1, 0);
    Backbuffer = SDL_GetWindowSurface(Window);
    
    float timeLastMs, timeCurrentMs, timeDeltaMs,
            timeAccumulatedMs, timeStepMs;

    timeStepMs = 1000 / 60; //60hz
    
    while(gameLoop == 1)
    {   
        timeLastMs = timeCurrentMs;
        timeCurrentMs = SDL_GetTicks();
        timeDeltaMs = timeCurrentMs - timeLastMs;
        timeAccumulatedMs += timeDeltaMs;
        
       
        if(initVel < maxVel){
             initVel += timeDeltaMs;
        }
       
        SDL_bool collision = SDL_HasIntersection(&snake, &food);
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        if(snake.x >= 1600 || snake.x <= 0 || snake.y >= 900 || snake.y <= 0){
            Dead();
        }
        if (collision)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &snake);

        if (collision){
            snake.w += 10;
            for(int i = 0; i < 4; i++){
                x[i] = rand() % 1300;
                food.x = x[2];
                food.y = x[3] / 2;
            }
        }
        else
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        SDL_RenderFillRect(renderer, &food);
        SDL_UpdateWindowSurface(Window);
        SDL_RenderPresent(renderer);
       
        if(direction == 1){
            snake.x += initVel * timeDeltaMs;
        }
        else if(direction == 2){
            snake.x -= initVel * timeDeltaMs;
        } else if(direction == 3){
            snake.y -= initVel * timeDeltaMs;
        } else{
            snake.y += initVel * timeDeltaMs;
        }
        while (timeAccumulatedMs >= timeStepMs)
        {
            Input();
            timeAccumulatedMs -= timeStepMs;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 0;
}
