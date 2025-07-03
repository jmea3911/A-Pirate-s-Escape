// MenuState.cpp
#include "gameOver.h"
#include "Game.h"     // para usar game->changeState(...)
#include "juego.h"  // el siguiente estado
#include <iostream>
#include "Settings.h"
#include "Menu.h"


void GameOver::init(Game* game) {
    
    fondo = new Objetos("assets/Ocean.png", game->getRenderer());
    
    menu = new Objetos("assets/mnMenu.png", game->getRenderer());
   

    shipWreck = new Objetos("assets/shipwreck.png", game->getRenderer());
    
    menu->setHoverTexture("assets/mainMenu.png", game->getRenderer());
    
    gameOver = new Objetos("assets/gameOver.png", game->getRenderer());
    
    start = new Objetos("assets/startGame.png", game->getRenderer());
    
    start->setHoverTexture("assets/startSelc.png", game->getRenderer());
    
    
    
   
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

    
    fondo->setDestR(0, 0, 2400, 1200);
    
    fondo->Render();
    
    gameOver->setDestR(316, 160, 1170, 282);
    gameOver->Render();
    
    shipWreck->setDestR(540, 660, 720, 720);
    shipWreck->Render();
    
    start->setDestR(590, 600, 280, 232);
    start->Render();
    
    menu->setDestR(940, 600, 280, 232);
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
