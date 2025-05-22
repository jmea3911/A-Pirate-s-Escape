#pragma once

#include "Game.h"
#include "Texturas.h"

class Objetos {
    
public:
    Objetos(const char* archivo, SDL_Renderer* ren);
    
    void Update();
    void Render();
    void setDestR(int x, int y, int w, int h);
    void clean();
    
private:
    
    int xpos;
    int ypos;
    
    SDL_Texture* texture;
    SDL_FRect srcR{};
    SDL_FRect destR{};
    SDL_Renderer* renderer; 
    
};
