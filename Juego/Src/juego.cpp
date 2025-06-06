// MenuState.cpp
#include "juego.h"
#include "Game.h"     // para usar game->changeState(...)
//#include "JuegoState.h"  // el siguiente estado
#include <iostream>
//#include "ECS.h"
//#include "Components.h"




void Juego::init(Game* game) {
    
    barco = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/barcoPirata.png", game->getRenderer());
    fondo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/fondoJuego.png", game->getRenderer());
    
}

void Juego::handleEvents(Game* game, SDL_Event& event) {
    
    if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.scancode) {
                case SDL_SCANCODE_LEFT:
                    barcoX -= barcoVel;
                    break;
                case SDL_SCANCODE_RIGHT:
                    barcoX += barcoVel;
                    break;
//                case SDL_SCANCODE_A:
//                    barcoX -= barcoVel;
//                    break;
//                case SDL_SCANCODE_D:
//                    barcoX += barcoVel;
//                    break;
                default:
                    break;
            }
        }

}

void Juego::update(Game* game) {
    
    
  
      const bool* teclas = SDL_GetKeyboardState(nullptr);

        if (teclas[SDL_SCANCODE_LEFT]) {
            barcoX -= barcoVel;
            if (barcoX < 90) barcoX = 90; // evitar que se salga de la pantalla
        }
        if (teclas[SDL_SCANCODE_RIGHT]) {
            barcoX += barcoVel;
            if (barcoX > 900 - 170) barcoX = 900 - 170; // 900 ancho ventana - 80 ancho barco
        }
    
    Uint64 ahora = SDL_GetTicks();
    if (ahora - tiempoObstaculo > intervaloObstaculo) {
        
        
        int margen = 90;
        int xRandom = margen + (rand() % (900 - 2 * margen - 80));

        //int xRandom = rand() % (900 - 80);
        obstaculos.push_back(new Obstaculos("/Users/jmea/Documents/Juego/Juego/assets/boulder.png", game->getRenderer(), xRandom, -80, 0.25f));
        tiempoObstaculo = ahora;
    }
    
    for (auto it = obstaculos.begin(); it != obstaculos.end(); ) {
        (*it)->update();
        if ((*it)->estaFueraDePantalla(600)) {
            delete *it;
            it = obstaculos.erase(it);
        } else {
            ++it;
        }
    }
}

void Juego::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);
    
    fondo->setDestR(0, 0, 900, 600);
    fondo->Render();
    
    barco->setDestR(barcoX, barcoY, 80, 120);
    barco->Render();
    
    for (auto& obst : obstaculos) {
            obst->render();
        }
    
    

    
    
    
    
}

void Juego::onExit(Game* game) {
    
}
