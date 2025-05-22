#include "Game.h"
#include "Texturas.h"
#include "Objetos.h"

using namespace std;

Objetos* fondo;
Objetos* cofre;
Objetos* titulo;
Objetos* start;
Objetos* load;
Objetos* settings;




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
    
    start = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/startGame.png", renderer);
    start->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/startSelc.png", renderer);
    
    load = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/loadGame.png", renderer);
    load->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/loadSelc.png", renderer);
    
    settings = new Objetos("/Users/jmea/Documents/Juego/Juego/assets/settings.png", renderer);
    settings->setHoverTexture("/Users/jmea/Documents/Juego/Juego/assets/settingsSelc.png", renderer);
    
    
    
}

void Game::handleEvents()
{
	SDL_Event event;

	switch (event.type)
	{
	    case SDL_EVENT_QUIT :
		    isRunning = false;
		    break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Verifica si se presionó el botón
                if (start->isClicked(mouseX, mouseY)) {
                    std::cout << "Botón presionado" << std::endl;
                }
                else if (load->isClicked(mouseX, mouseY)) {
                    std::cout << "Botón presionado" << std::endl;
                }
                else if (settings->isClicked(mouseX, mouseY)) {
                    std::cout << "Botón presionado" << std::endl;
                }
            }
            break;
            
        case SDL_EVENT_MOUSE_MOTION: {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            // Evaluar cada botón de forma separada
            start->setHovering(start->isClicked(mouseX, mouseY));
            load->setHovering(load->isClicked(mouseX, mouseY));
            settings->setHovering(settings->isClicked(mouseX, mouseY));
            //settings->setHovering(settings->isClicked(mouseX, mouseY));
            // y así con todos los botones...

            break;
        }

        
            /*
        case SDL_EVENT_MOUSE_MOTION: {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            
            if (start->isClicked(mouseX, mouseY)) {
                start->setHovering(true);
            } else if (!start->isClicked(mouseX, mouseY)){
                start->setHovering(false);
            }
            else if (load->isClicked(mouseX, mouseY)) {
                load->setHovering(true);
            }
            else if (!load->isClicked(mouseX, mouseY)) {
                load->setHovering(false);
            }
            
            break;
        }
             */
            
        

            
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
    
    start->setDestR(220, 300, 140, 116);
    start->Render();
    
    load->setDestR(440, 300, 140, 116);
    load->Render();
    
    settings->setDestR(15, 543, 130, 56);
    settings->Render();
    
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
    //fondo.clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
