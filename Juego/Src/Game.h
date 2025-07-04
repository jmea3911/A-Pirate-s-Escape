#pragma once


#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include "Texturas.h"
#include "GameState.h"
#include <SDL3_mixer/SDL_mixer.h>

extern Mix_Music* musicaFondo;
extern Mix_Chunk* selec;



class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
    SDL_Renderer* getRenderer();
    void changeState(GameState* newState);
    
    

private:
	bool isRunning = true;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_FRect srcR, destR;
    GameState* currentState;
    
};
