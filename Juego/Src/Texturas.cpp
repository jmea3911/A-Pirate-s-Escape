#include "Texturas.h"

    

SDL_Texture* Texturas::cargarTextura(const char *archivo, SDL_Renderer *renderer){
    SDL_Surface* tempSurface = IMG_Load(archivo);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    
    return tex;
}


