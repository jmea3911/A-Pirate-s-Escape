#include "proyectil.h"

proyectil::proyectil(int x, int y) {
    rect.x = x;
    rect.y = y;
    rect.w = 10; // Ancho del proyectil
    rect.h = 20; // Alto del proyectil
    velocidad = 7.0f; // Velocidad hacia arriba
}

void proyectil::mover() {
    moverProyectil(&rect.y, velocidad);

}

void proyectil::render(SDL_Renderer* renderer) {
    // Puedes personalizar el color del proyectil
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Rojo
    SDL_RenderFillRect(renderer, &rect);
}

bool proyectil::estaFueraDePantalla() const {
    return (rect.y + rect.h) < 0; // Si ya salió por la parte superior
}
