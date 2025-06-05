// MenuState.h
#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"

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
};

