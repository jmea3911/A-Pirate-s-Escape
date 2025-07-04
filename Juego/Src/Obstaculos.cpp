#include "Obstaculos.h"

extern "C" void moverObjeto(int* y, int velocidad);


Obstaculos::Obstaculos(const char* archivo, SDL_Renderer* renderer, int x, int y, float velocidad)
    : x(x), posY(static_cast<float>(y)), velocidad(velocidad)
{
    objeto = new Objetos(archivo, renderer);
    objeto->setDestR(x, y, ancho, alto);
}

void Obstaculos::update() {

    int posYint = static_cast<int>(posY);

    moverObjeto(&posYint, static_cast<int>(velocidad));

    posY = static_cast<float>(posYint);
    objeto->setDestR(x, static_cast<int>(posY), ancho, alto);


    // posY += velocidad;
    // objeto->setDestR(x, static_cast<int>(posY), ancho, alto);
}

void Obstaculos::render() {
    objeto->Render();
}

SDL_Rect Obstaculos::getRect() const {
    return SDL_Rect{ x, static_cast<int>(posY), ancho, alto };
}

bool Obstaculos::estaFueraDePantalla(int altoVentana) const {
    return static_cast<int>(posY) > altoVentana;
}

