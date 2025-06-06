// MenuState.cpp
#include "Settings.h"
#include "Game.h"     // para usar game->changeState(...)
#include "Menu.h"  // el siguiente estado
#include <iostream>




void Settings::init(Game* game) {
    fondo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/Ocean.png", game->getRenderer());
   

    UI = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/settingsUI.png", game->getRenderer());
    
    equis = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/xBoton.png", game->getRenderer());
    
    
}

void Settings::handleEvents(Game* game, SDL_Event& event) {
//
    switch (event.type)
    {
            
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                
                // Verifica si se presionó el botón
                if (equis->isClicked(mouseX, mouseY)) {
                    std::cout << "Botón presionado" << std::endl;
                    game->changeState(new Menu());
                    
                }
                break;
                
                //        case SDL_EVENT_MOUSE_MOTION: {
                //            int mouseX = event.motion.x;
                //            int mouseY = event.motion.y;
                //
                //
                //
                //            break;
                //        }
            }
    }
}

void Settings::update(Game* game) {
    // No hay lógica en el menú por ahora
}

void Settings::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);

    
    fondo->setDestR(0, 0, 1200, 600);
    fondo->Render();
    
    UI->setDestR(309, 100, 283, 400);
    UI->Render();
    
    equis->setDestR(315, 106, 35, 35);
    equis->Render();
    
    
}

void Settings::onExit(Game* game) {
    fondo->clean();
    delete fondo;
    fondo = nullptr;

    UI->clean();
    delete UI;
    UI = nullptr;
    
    
}

