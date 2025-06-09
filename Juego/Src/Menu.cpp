// MenuState.cpp
#include "Menu.h"
#include "Game.h"     // para usar game->changeState(...)
#include "juego.h"  // el siguiente estado
#include <iostream>
#include "Settings.h"



void Menu::init(Game* game) {
    fondo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/Ocean.png", game->getRenderer());
   

    start = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/startGame.png", game->getRenderer());
    
    start->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/startSelc.png", game->getRenderer());
    
    cofre = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/cofre.png", game->getRenderer());
    
    titulo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/TituloJuego.png", game->getRenderer());
    
    load = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/loadGame.png", game->getRenderer());
    load->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/loadSelc.png", game->getRenderer());
    
    settings = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/settings.png", game->getRenderer());
    settings->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/settingsSelc.png", game->getRenderer());
}

void Menu::handleEvents(Game* game, SDL_Event& event) {
//    int mouseX = event.motion.x;
//    int mouseY = event.motion.y;
//
//    switch (event.type) {
//        case SDL_EVENT_MOUSE_MOTION:
//            startButton->setHovering(startButton->isClicked(mouseX, mouseY));
//            break;
//
//        case SDL_EVENT_MOUSE_BUTTON_DOWN:
//            if (startButton->isClicked(mouseX, mouseY)) {
//                std::cout << "Iniciando nuevo juego..." << std::endl;
//                //game->changeState(new JuegoState());
//            }
//            break;
//
//        default:
//            break;
//    }
    

    switch (event.type)
    {
            
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                
                // Verifica si se presionó el botón
                if (start->isClicked(mouseX, mouseY)) {
                    game->changeState(new Juego());
                }
                else if (load->isClicked(mouseX, mouseY)) {
                //codigo del guardado
                }
                else if (settings->isClicked(mouseX, mouseY)) {
                    game->changeState(new Settings());
                }
            }
            break;
            
        case SDL_EVENT_MOUSE_MOTION: {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            
            // Evaluar cada botón de forma separada
            start->setHovering(start->isClicked(mouseX, mouseY));
            load->setHovering(load->isClicked(mouseX, mouseY));
            settings->setHovering(settings->isClicked(mouseX, mouseY));
            //settings->setHovering(settings->isClicked(mouseX, mouseY));
            // y así con todos los botones...
            
            break;
        }
    }
}

void Menu::update(Game* game) {
    // No hay lógica en el menú por ahora
}

void Menu::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);

    
    fondo->setDestR(0, 0, 1200, 600);
    fondo->Render();
    
    

    
    cofre->setDestR(290, 380, 270, 220);
    cofre->Render();
    
    titulo->setDestR(230, 10, 440, 220);
    titulo->Render();
    
    start->setDestR(290, 300, 140, 116);
    start->Render();
    
    load->setDestR(470, 300, 140, 116);
    load->Render();
    
    settings->setDestR(15, 543, 130, 56);
    settings->Render();
    
    
}

void Menu::onExit(Game* game) {
    fondo->clean();
    delete fondo;
    fondo = nullptr;

    start->clean();
    delete start;
    startButton = nullptr;
    
    cofre->clean();
    delete cofre;
    cofre = nullptr;

    titulo->clean();
    delete titulo;
    titulo = nullptr;

    

    load->clean();
    delete load;
    load = nullptr;

    settings->clean();
    delete settings;
    settings = nullptr;

}
