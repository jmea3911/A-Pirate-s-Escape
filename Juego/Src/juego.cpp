// MenuState.cpp
#include "juego.h"
#include "Game.h"     // para usar game->changeState(...)
//#include "JuegoState.h"  // el siguiente estado
#include <iostream>
//#include "ECS.h"
//#include "Components.h"
#include "gameOver.h"




void Juego::init(Game* game) {
    
    barco = new Objetos("assets/barcoPirata.png", game->getRenderer());
    fondo = new Objetos("assets/fondoJuego.png", game->getRenderer());
    
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

bool colisiona(const SDL_Rect& a, const SDL_Rect& b) {
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}


void Juego::update(Game* game) {
    
    
  
      const bool* teclas = SDL_GetKeyboardState(nullptr);

        if (teclas[SDL_SCANCODE_LEFT]) {
            barcoX -= barcoVel;
            if (barcoX < 180) barcoX = 180; // evitar que se salga de la pantalla
        }
        if (teclas[SDL_SCANCODE_RIGHT]) {
            barcoX += barcoVel;
            if (barcoX > 1800 - 340) barcoX = 1800 - 340; // 900 ancho ventana - 80 ancho barco
            
        }
    
    
    // Rectángulo del barco
        SDL_Rect rectBarco = { barcoX + 20, barcoY + 30, 120, 180 };

        // Generar obstáculos (omitido aquí...)

        // Actualizar y chequear colisión
        for (auto it = obstaculos.begin(); it != obstaculos.end(); ) {
            (*it)->update();

            if (colisiona(rectBarco, (*it)->getRect())) {
                
                
                game->changeState(new GameOver());
                return;
            }

            if ((*it)->estaFueraDePantalla(1200)) {
                delete *it;
                it = obstaculos.erase(it);
            } else {
                ++it;
            }
        }
    
    Uint64 ahora = SDL_GetTicks();
    if (ahora - tiempoObstaculo > intervaloObstaculo + variacionAleatoria) {
        
        
        int margen = 180;
        int xRandom = margen + (rand() % (1800 - 2 * margen - 160));
        
        const char* ruta = rand() % 2 == 0
                ? "assets/boulder.png"
                : "assets/barril.png";

            obstaculos.push_back(new Obstaculos(ruta, game->getRenderer(), xRandom, -80, 1.0f));
        
        tiempoObstaculo = ahora;
        variacionAleatoria = rand() % 1000;
    }
    
    
    
    for (auto it = obstaculos.begin(); it != obstaculos.end(); ) {
        (*it)->update();
        if ((*it)->estaFueraDePantalla(1200)) {
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
    
    fondo->setDestR(0, 0, 1800, 1200);
    fondo->Render();
    
    barco->setDestR(barcoX, barcoY, 160, 240);
    barco->Render();
    
    for (auto& obst : obstaculos) {
            obst->render();
        }
    
    

    
    
    
    
}

void Juego::onExit(Game* game) {
    
}
