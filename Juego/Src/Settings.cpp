// MenuState.cpp
#include "Settings.h"
#include "Game.h"     // para usar game->changeState(...)

#include <iostream>




void Settings::init(Game* game) {
    fondo = new Objetos("assets/Ocean.png", game->getRenderer());
   

    UI = new Objetos("assets/settingsUI.png", game->getRenderer());
    
    equis = new Objetos("assets/xBoton.png", game->getRenderer());
    mute = new Objetos("assets/mute.png", game->getRenderer());

    selec = Mix_LoadWAV("assets/selec.mp3");
    
    
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
                    Mix_PlayChannel(-1, selec, 0);
                    game->changeState(new Menu());
                    return;
                    
                }
                if (mute->isClicked(mouseX, mouseY)) {
    if (audioActivo) {
        Mix_HaltMusic(); // Detener la música
        Mix_Volume(-1, 0); // Silenciar todos los canales
        Mix_VolumeMusic(0); // Silenciar la música
        audioActivo = false;
        std::cout << "Audio desactivado" << std::endl;
    } else {
        Mix_Volume(-1, MIX_MAX_VOLUME); // Reactivar volumen completo
        Mix_VolumeMusic(MIX_MAX_VOLUME); // Reactivar volumen música
        Mix_PlayMusic(musicaFondo, -1); // 🔥 Volver a reproducir la música
        audioActivo = true;
        std::cout << "Audio activado" << std::endl;
    }
}

                break;
                 
            }
    }

   
}



void Settings::update(Game* game) {
    // No hay lógica en el menú por ahora
}

void Settings::render(Game* game) {
    
    

    SDL_Event event;
    SDL_PollEvent(&event);

    
    fondo->setDestR(0, 0, 2400, 1200);
    fondo->Render();
    
    UI->setDestR(618, 200, 566, 800);
    UI->Render();
    
    equis->setDestR(630, 212, 70, 70);
    equis->Render();

    mute->setDestR(808, 530, 175, 175);
    mute->Render();
    
    
}

void Settings::onExit(Game* game) {
    if (fondo) {
        fondo->clean();
        delete fondo;
        fondo = nullptr;
    }

    if (UI) {
        UI->clean();
        delete UI;
        UI = nullptr;
    }

    if (equis) {
        equis->clean();
        delete equis;
        equis = nullptr;
    }

    if (mute) {
        mute->clean();
        delete mute;
        mute = nullptr;
    }

    if (selec) {
        Mix_FreeChunk(selec);
        selec = nullptr;
    }
}


