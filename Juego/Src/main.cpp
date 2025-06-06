#include "Game.h"
using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[])
{
    std::cout << "Antes de SDL_Init" << std::endl;
    int init_result = SDL_Init(SDL_INIT_VIDEO);
    std::cout << "Resultado SDL_Init: " << init_result << std::endl;
    if (init_result != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        
    }
    
  
    
	game = new Game();
	game->init("GameWindow", 900, 600, false);


	while (game->running())
	{
		game->handleEvents();

		game->update();
     
		game->render();
     
	}

	game->clean();
	return 0;
}


 
 
