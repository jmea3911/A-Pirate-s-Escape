#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"
#include "Obstaculos.h"


class GameOver : public GameState {
private:
    Objetos* gameOver;
    Objetos* menu;
    Objetos* menuSelec;
    Objetos* shipWreck;
    Objetos* start;
    Objetos* fondo;
    

public:
    void init(Game* game) override;
    void handleEvents(Game* game, SDL_Event& event) override;
    void update(Game* game) override;
    void render(Game* game) override;
    void onExit(Game* game) override;
    
};
