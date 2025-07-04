// MenuState.h
#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"
#include <SDL3_mixer/SDL_mixer.h>

extern bool audioActivo;





class Menu : public GameState {
private:
    Objetos* startButton;
    Objetos* fondo;
    Objetos* cofre;
    Objetos* titulo;
    Objetos* start;
    Objetos* load;
    Objetos* settings;
    
    

public:
    void init(Game* game) override;
    void handleEvents(Game* game, SDL_Event& event) override;
    void update(Game* game) override;
    void render(Game* game) override;
    void onExit(Game* game) override;
    //Mix_Music* musicaFondo = nullptr;
    Mix_Chunk* selec = nullptr;
    bool audioActivo = true;

};

