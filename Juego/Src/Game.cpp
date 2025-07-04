#include "Game.h"
#include "Texturas.h"
#include "Objetos.h"
#include "Menu.h"

using namespace std;

Mix_Music* musicaFondo = nullptr;




Game::Game()
{}

Game::~Game()
{
    Mix_HaltMusic();
Mix_FreeMusic(musicaFondo);
Mix_CloseAudio();
Mix_Quit();

}

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
    
    currentState = new Menu();
    currentState->init(this);

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);


    if (!Mix_OpenAudio(0, nullptr)) {
        std::cout << "Error al abrir audio: " << SDL_GetError() << std::endl;
    }

    // Cargar la música
    musicaFondo = Mix_LoadMUS("assets/loop.mp3");
    if (!musicaFondo) {
        std::cout << "Error al cargar la música: " << SDL_GetError() << std::endl;
    }

    if (audioActivo && !Mix_PlayingMusic()) {
    Mix_PlayMusic(musicaFondo, -1);
    }
    
    
}

void Game::changeState(GameState* newState) {
    if (currentState) {
        currentState->onExit(this);
        delete currentState;
    }
    
    currentState = newState;
    currentState->init(this);
    
}

void Game::handleEvents()
{
	SDL_Event event;
    
    

        while (SDL_PollEvent(&event)) {
            // Salida global del juego
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }

            // Delegar el evento al estado actual
            if (currentState) {
                currentState->handleEvents(this, event);
            }
        }
    

            
	    
	
}

void Game::update()
{
    
    currentState->update(this);

}

SDL_Renderer* Game::getRenderer(){
    return renderer;
}

void Game::render()
{

    
    SDL_Event event;
    SDL_PollEvent(&event);

	SDL_RenderClear(renderer);
    
    currentState->render(this);
    
   /*
    fondo->setDestR(0, 0, 1200, 600);
    fondo->Render();
    
    cofre->setDestR(240, 380, 270, 220);
    cofre->Render();
    
    titulo->setDestR(180, 10, 440, 220);
    titulo->Render();
    
    start->setDestR(220, 300, 140, 116);
    start->Render();
    
    load->setDestR(440, 300, 140, 116);
    load->Render();
    
    settings->setDestR(15, 543, 130, 56);
    settings->Render();
    */
    
    

    
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
    //fondo.clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
