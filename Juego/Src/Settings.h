
#pragma once
#include <SDL3/SDL.h>
#include "GameState.h"
#include "Objetos.h"
#include "Game.h"
#include "Menu.h"  // el siguiente estado

class Settings : public GameState {
private:
    Objetos* UI;
    Objetos* fondo;
    Objetos* equis;
    Objetos* mute;
    
    

public:
    void init(Game* game) override;
    void handleEvents(Game* game, SDL_Event& event) override;
    void update(Game* game) override;
    void render(Game* game) override;
    void onExit(Game* game) override;
    Mix_Chunk* selec = nullptr;
};

