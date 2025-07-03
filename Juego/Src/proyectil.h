

#include <SDL3/SDL.h>

class proyectil {
public:
    SDL_FRect rect;      // Rectángulo del proyectil
    float velocidad;    // Velocidad vertical del proyectil

    proyectil(int x, int y); // Constructor
    void mover();            // Movimiento hacia arriba
    void render(SDL_Renderer* renderer); // Dibujar el proyectil
    bool estaFueraDePantalla() const; // Verifica si ya salió de la pantalla
};


