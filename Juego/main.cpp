

#include "SDL3/SDL.h"
#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Menu", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

   
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); // azul claro
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

