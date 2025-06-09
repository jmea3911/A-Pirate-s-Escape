// MenuState.cpp
#include "gameOver.h"
#include "Game.h"     // para usar game->changeState(...)
#include "juego.h"  // el siguiente estado
#include <iostream>
#include "Settings.h"
#include "Menu.h"


void GameOver::init(Game* game) {
    
    fondo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/Ocean.png", game->getRenderer());
    
    menu = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/mnMenu.png", game->getRenderer());
   

    shipWreck = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/shipwreck.png", game->getRenderer());
    
    menu->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/mainMenu.png", game->getRenderer());
    
    gameOver = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/gameOver.png", game->getRenderer());
    
    start = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/startGame.png", game->getRenderer());
    
    start->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/startSelc.png", game->getRenderer());
    
    
    
   
}

void GameOver::handleEvents(Game* game, SDL_Event& event) {


    switch (event.type)
    {
            
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                
                // Verifica si se presionó el botón
                if (menu->isClicked(mouseX, mouseY)) {
                    game->changeState(new Menu());
                }
                else if (start->isClicked(mouseX, mouseY)) {
                
                    game->changeState(new Juego());
                }
                
            }
            break;
            
        case SDL_EVENT_MOUSE_MOTION: {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            
            // Evaluar cada botón de forma separada
            start->setHovering(start->isClicked(mouseX, mouseY));
            menu->setHovering(menu->isClicked(mouseX, mouseY));
            
            
            break;
        }
    }
}

void GameOver::update(Game* game) {
    // No hay lógica en el menú por ahora
}

void GameOver::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);

    
    fondo->setDestR(0, 0, 1200, 600);
    
    fondo->Render();
    
    gameOver->setDestR(158, 80, 585, 141);
    gameOver->Render();
    
    shipWreck->setDestR(270, 330, 360, 360);
    shipWreck->Render();
    
    start->setDestR(290, 300, 140, 116);
    start->Render();
    
    menu->setDestR(470, 300, 140, 116);
    menu->Render();
    
    
    
    
}

void GameOver::onExit(Game* game) {
    fondo->clean();
    delete fondo;
    fondo = nullptr;

    start->clean();
    delete start;
    start = nullptr;
    
    menu->clean();
    delete menu;
    menu = nullptr;

    shipWreck->clean();
    delete shipWreck;
    shipWreck = nullptr;

    

    gameOver->clean();
    delete gameOver;
    gameOver = nullptr;

}
