#pragma once
#include "Objetos.h"
#include <SDL3/SDL.h>

class Obstaculos {
    
public:
    Obstaculos(const char* archivo, SDL_Renderer* renderer, int x, int y, float velocidad);

    void update();                  // Mover hacia abajo
    void render();                  // Dibujar en pantalla
    SDL_Rect getRect() const;      // Obtener área para colisión

    bool estaFueraDePantalla(int altoVentana) const;

private:
    Objetos* objeto;
    int x;
    float posY;
    float velocidad;
    int ancho = 80;
    int alto = 80;
};

