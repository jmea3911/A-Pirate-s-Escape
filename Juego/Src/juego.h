
#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"
#include <vector>
#include "Obstaculos.h"
#include "proyectil.h"
#include <cstdlib>   // para rand() y srand()
#include <ctime>     // para time()
#include <algorithm>
#include <SDL3_mixer/SDL_mixer.h>


    bool cargarJuego(int &nivel, int &destruidos, float &velocidad, int &obstaculosNivel, int &intervalo);
extern "C" void moverBarco(int* x, int velocidad, int direccion);




class Juego : public GameState {
private:
    Objetos* barco;
    Objetos* fondo;

    Objetos* pausa;
    Objetos* guardar;
    Objetos* reanudar;

    
    

public:
    void init(Game* game) override;
    void handleEvents(Game* game, SDL_Event& event) override;
    void update(Game* game) override;
    void render(Game* game) override;
    void onExit(Game* game) override;


    
    int barcoX = 780;      // posición inicial
    int barcoY = 900;
    int barcoVel = 2;      // velocidad en píxeles/frame
    bool moviendoDerecha = true;

    int nivel = 1;
    int contadorObstaculosDestruidos = 0;
    int obstaculosParaSubirNivel = 15;
    float velocidadObstaculos = 1.0f;

    
    std::vector<Obstaculos*> obstaculos;
    std::vector<proyectil> proyectiles;
    

    std::vector<SDL_Texture*> nivelesTexturas;

    SDL_Renderer *renderer;
    int tiempoObstaculo = 0;
    int intervaloObstaculo = 1500;
    int variacionAleatoria = 0;
    SDL_Rect rectBarco;

    bool mostrarControles = true;
    Objetos* controles;

    bool juegoPausado = false;
    bool mostrarMenuPausa = false;

    Mix_Chunk* barcoDest = nullptr;
    Mix_Chunk* objetoDest = nullptr;
    Mix_Chunk* selec = nullptr;


};


