// GameState.h
#pragma once
#include <SDL3/SDL.h>

class Game;

class GameState {
public:
    virtual void handleEvents(Game* game, SDL_Event& event) = 0;
    virtual void update(Game* game) = 0;
    virtual void render(Game* game) = 0;
    virtual void init(Game* game) = 0;
    virtual void onExit(Game* game) = 0;
    virtual ~GameState() {}
};

