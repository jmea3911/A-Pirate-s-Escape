// MenuState.cpp
#include "juego.h"
#include "Game.h"     // para usar game->changeState(...)
//#include "JuegoState.h"  // el siguiente estado
#include <iostream>



void Juego::init(Game* game) {
    
    barco = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/barcoPirata.png", game->getRenderer());
    
}

void Juego::handleEvents(Game* game, SDL_Event& event) {

}

void Juego::update(Game* game) {
    // No hay lógica en el menú por ahora
}

void Juego::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);
    
    barco->setDestR(340, 450, 80, 120);
    barco->Render();

    
    
    
    
}

void Juego::onExit(Game* game) {
    
}
