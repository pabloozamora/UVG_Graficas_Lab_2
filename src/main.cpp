#include <SDL.h>
#include "framebuffer.h"

int x = 0;
int y = 0;

int main(int argv, char** args)
{
    createFrameBuffer();
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Lab 2: Conway's Game Of Life", 150, 70, 1200, 700, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    
    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Renderizar el juego
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);
        renderGame(renderer);
        updateGame(renderer);
        renderBuffer(renderer);
        SDL_RenderPresent(renderer);


        SDL_Delay(100);
    }

    return 0;
}