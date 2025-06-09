
#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"
#include <vector>
#include "Obstaculos.h"
#include <cstdlib>   // para rand() y srand()
#include <ctime>     // para time()


class Juego : public GameState {
private:
    Objetos* barco;
    Objetos* fondo;
    
    

public:
    void init(Game* game) override;
    void handleEvents(Game* game, SDL_Event& event) override;
    void update(Game* game) override;
    void render(Game* game) override;
    void onExit(Game* game) override;
    
    int barcoX = 390;      // posición inicial
    int barcoY = 450;
    int barcoVel = 1;      // velocidad en píxeles/frame
    bool moviendoDerecha = true;
    
    std::vector<Obstaculos*> obstaculos;
    
    Uint64 tiempoObstaculo = 0;
    Uint64 intervaloObstaculo = 1500;
    int variacionAleatoria = 0;
};


