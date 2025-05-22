#pragma once


#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include "Texturas.h"


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
    

private:
	bool isRunning = true;
	int cnt = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;
    SDL_FRect srcR, destR;
    
};
