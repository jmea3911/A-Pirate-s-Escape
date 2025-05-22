#pragma once

#include "Game.h"

class Texturas {
    
public:
    
    SDL_Texture* texture = nullptr;
    SDL_FRect srcR;
    SDL_FRect destR;
    
    static SDL_Texture* cargarTextura(const char* archivo, SDL_Renderer* renderer);
    
   
};
