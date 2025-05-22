#include "Game.h"
#include "Texturas.h"
#include "Objetos.h"

using namespace std;

Objetos* fondo;
Objetos* cofre;
Objetos* titulo;





Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
    
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
    else {
        flags = SDL_WINDOW_RESIZABLE;
    }

	if (SDL_Init(SDL_INIT_VIDEO) == 1)
	{
        
        window = SDL_CreateWindow(title, width, height, flags);
        renderer = SDL_CreateRenderer(window, NULL);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
            
            cout<<"RENDERED"<<endl;
            
		}

		isRunning = true;
	}
    
    
    fondo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/Ocean.png", renderer);
    
    cofre = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/cofre.png", renderer);
    
    titulo = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/TituloJuego.png", renderer);
    
    
    
}

void Game::handleEvents()
{
	SDL_Event event;

	switch (event.type)
	{
	case SDL_EVENT_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

}

void Game::render()
{
    
    
    SDL_Event event;
    SDL_PollEvent(&event);

	SDL_RenderClear(renderer);
    
    fondo->setDestR(0, 0, 1200, 600);
    fondo->Render();
    
    cofre->setDestR(240, 380, 270, 220);
    cofre->Render();
    
    titulo->setDestR(180, 10, 440, 220);
    titulo->Render();
    
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
    //fondo.clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
