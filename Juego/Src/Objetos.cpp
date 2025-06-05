
#include "Objetos.h"
#include "Texturas.h"


Objetos::Objetos(const char* archivo, SDL_Renderer* ren){
    
 
    renderer = ren;
    texture = Texturas::cargarTextura(archivo, renderer);
    
    if (!texture) {
        std::cout << "Fallo al cargar textura: " << archivo << " - " << SDL_GetError() << std::endl;
    }
    
    if (!ren) {
        std::cout << "Renderer recibido en Objetos es nullptr!" << std::endl;
    }


    
    float w = 0, h = 0;
    SDL_GetTextureSize(texture, &w, &h);

    srcR = { 0.0f, 0.0f, (float)w, (float)h };
    destR = srcR;
    
    
     
}

void Objetos::Update(){
    
}

void Objetos::setDestR(int x, int y, int w, int h){
    destR.x = x;
    destR.y = y;
    destR.w = w;
    destR.h = h;
}

void Objetos::Render() {
    SDL_Texture* currentTexture = hovering && hoverTexture ? hoverTexture : texture;
    SDL_RenderTexture(renderer, currentTexture, &srcR, &destR);
}


bool Objetos::isClicked(int mouseX, int mouseY){
    return mouseX >= destR.x && mouseX <= destR.x + destR.w &&
               mouseY >= destR.y && mouseY <= destR.y + destR.h;
    
}

void Objetos::setHoverTexture(const char* archivo, SDL_Renderer* ren) {
    hoverTexture = Texturas::cargarTextura(archivo, ren);
}

void Objetos::setHovering(bool isHovering) {
    hovering = isHovering;
}



void Objetos::clean() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
