// MenuState.cpp
#include "juego.h"
#include "Game.h"     // para usar game->changeState(...)
//#include "JuegoState.h"  // el siguiente estado
#include <iostream>
//#include "ECS.h"
//#include "Components.h"
#include "gameOver.h"
#include "Menu.h"
#include <fstream>

bool audioActivo = true;





void guardarJuego(int nivel, int destruidos, float velocidad, int obstaculosNivel, int intervalo) {
    std::ofstream file("save.txt");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
        return;
    }

    file << "Nivel: " << nivel << std::endl;
    file << "Destruidos: " << destruidos << std::endl;
    file << "Velocidad: " << velocidad << std::endl;
    file << "ObstaculosNivel: " << obstaculosNivel << std::endl;
    file << "Intervalo: " << intervalo << std::endl;

    file.close();
    std::cout << "Partida guardada exitosamente." << std::endl;
}

#include <fstream>
#include <iostream>

bool cargarJuego(int &nivel, int &destruidos, float &velocidad, int &obstaculosNivel, int &intervalo) {
    std::ifstream file("save.txt");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
        return false;
    }

    std::string etiqueta;

    // leer y asignar cada valor
    file >> etiqueta >> nivel;
    file >> etiqueta >> destruidos;
    file >> etiqueta >> velocidad;
    file >> etiqueta >> obstaculosNivel;
    file >> etiqueta >> intervalo;

    file.close();
    std::cout << "Partida cargada exitosamente." << std::endl;
    return true;
}





void Juego::init(Game* game) {
    
    barco = new Objetos("assets/barcoPirata.png", game->getRenderer());
    fondo = new Objetos("assets/fondoJuego.png", game->getRenderer());
    controles = new Objetos("assets/teclas.png", game->getRenderer());

    pausa = new Objetos("assets/pausa.png", game->getRenderer());
    guardar = new Objetos("assets/guardar.png", game->getRenderer());
    guardar->setHoverTexture("assets/guardarSelec.png", game->getRenderer());
    reanudar = new Objetos("assets/Reanudar.png", game->getRenderer());
    reanudar->setHoverTexture("assets/ReanudarSelec.png", game->getRenderer());

    for (int i = 1; i <= 5; ++i) {
    std::string ruta = "assets/NIVEl " + std::to_string(i) + ".png";

    SDL_Texture* texture = Texturas::cargarTextura(ruta.c_str(), game->getRenderer());
    if (!texture) {
        std::cout << "Error cargando " << ruta << std::endl;
        continue;
    }

    nivelesTexturas.push_back(texture);
}
    
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);


    if (!Mix_OpenAudio(0, nullptr)) {
        std::cout << "Error al abrir audio: " << SDL_GetError() << std::endl;
    }

    // Cargar la música
   
    barcoDest = Mix_LoadWAV("assets/barcoDest.mp3");
    objetoDest = Mix_LoadWAV("assets/objetodest.mp3");
    selec = Mix_LoadWAV("assets/selec.mp3");
    

    
}

void Juego::handleEvents(Game* game, SDL_Event& event) {
    // Pantalla de controles
    if (mostrarControles) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.scancode == SDL_SCANCODE_RETURN) {
                mostrarControles = false; // Salir de la pantalla de controles
            }
        }
        return; // Mientras muestro controles, no manejo más eventos
    }

    // Menú de pausa
    if (juegoPausado && mostrarMenuPausa) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (reanudar->isClicked(mouseX, mouseY)) {
                Mix_PlayChannel(-1, selec, 0);
                juegoPausado = false;
                mostrarMenuPausa = false;
            }
            else if (guardar->isClicked(mouseX, mouseY)) {
                Mix_PlayChannel(-1, selec, 0);
                guardarJuego(nivel, contadorObstaculosDestruidos, velocidadObstaculos, obstaculosParaSubirNivel, intervaloObstaculo);

                game->changeState(new Menu()); // Regresar al menú principal
            }
        }

        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            reanudar->setHovering(reanudar->isClicked(mouseX, mouseY));
            guardar->setHovering(guardar->isClicked(mouseX, mouseY));
        }

        return; // Mientras estamos en el menú de pausa, no procesamos más eventos del juego
    }

    // Eventos del juego
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.scancode) {
            case SDL_SCANCODE_P:
                juegoPausado = !juegoPausado;
                mostrarMenuPausa = juegoPausado;
                break;

            default:
                // Solo permitir mover el barco si el juego NO está pausado
                if (!juegoPausado) {
                    switch (event.key.scancode) {
                        case SDL_SCANCODE_LEFT:
                            moverBarco(&barcoX, barcoVel, -1);
                            break;

                        case SDL_SCANCODE_RIGHT:
                            moverBarco(&barcoX, barcoVel, 1);
                            break;

                        case SDL_SCANCODE_SPACE: {
                            int proyectilX = rectBarco.x + rectBarco.w / 2 - 5;
                            int proyectilY = rectBarco.y;
                            proyectiles.push_back(proyectil(proyectilX, proyectilY));
                            break;
                        }

                        default:
                            break;
                    }
                }
                break;
        }
    }
}


bool colisiona(const SDL_Rect& a, const SDL_Rect& b) {
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}


void Juego::update(Game* game) {

    if (mostrarControles) return;

    if (juegoPausado) return; 
  
      const bool* teclas = SDL_GetKeyboardState(nullptr);

        if (teclas[SDL_SCANCODE_LEFT]) {
            barcoX -= barcoVel;
            if (barcoX < 180) barcoX = 180; // evitar que se salga de la pantalla
        }
        if (teclas[SDL_SCANCODE_RIGHT]) {
            barcoX += barcoVel;
            if (barcoX > 1800 - 340) barcoX = 1800 - 340; // 900 ancho ventana - 80 ancho barco
            
        }

        // Rectángulo del barco
     rectBarco = { barcoX + 20, barcoY + 30, 120, 180 };

        // Mover todos los proyectiles
        for (auto& proyectil : proyectiles) {
            proyectil.mover();
        }

// Eliminar los proyectiles que salieron de la pantalla
        proyectiles.erase(
        std::remove_if(proyectiles.begin(), proyectiles.end(),
                   [](const proyectil& p) { return p.estaFueraDePantalla(); }),
        proyectiles.end());

    
    
        // Actualizar y chequear colisión
        for (auto it = obstaculos.begin(); it != obstaculos.end(); ) {
            (*it)->update();

            if (colisiona(rectBarco, (*it)->getRect())) {
                Mix_PlayChannel(-1, barcoDest, 0);
                
                
                game->changeState(new GameOver());
                return;
            }

            if ((*it)->estaFueraDePantalla(1200)) {
                delete *it;
                it = obstaculos.erase(it);
            } else {
                ++it;
            }
        }
    
    Uint64 ahora = SDL_GetTicks();
    if (ahora - tiempoObstaculo > intervaloObstaculo + variacionAleatoria) {
        
        
        int margen = 180;
        int xRandom = margen + (rand() % (1800 - 2 * margen - 160));
        
        const char* ruta = rand() % 2 == 0
                ? "assets/boulder.png"
                : "assets/barril.png";

            obstaculos.push_back(new Obstaculos(ruta, game->getRenderer(), xRandom, -80, velocidadObstaculos));
        
        tiempoObstaculo = ahora;
        variacionAleatoria = rand() % 1000;
    }
    
    
    
    for (auto it = obstaculos.begin(); it != obstaculos.end(); ) {
        (*it)->update();
        if ((*it)->estaFueraDePantalla(1200)) {
            delete *it;
            it = obstaculos.erase(it);
        } else {
            ++it;
        }
    }

    // Verificar colisión de proyectiles con obstáculos
for (auto itProyectil = proyectiles.begin(); itProyectil != proyectiles.end(); ) {
    bool impacto = false;

    for (auto itObstaculo = obstaculos.begin(); itObstaculo != obstaculos.end(); ) {

        // Adaptar SDL_FRect del proyectil a SDL_Rect para usar la función colisiona
        SDL_Rect rectProyectil = { 
            static_cast<int>(itProyectil->rect.x),
            static_cast<int>(itProyectil->rect.y),
            static_cast<int>(itProyectil->rect.w),
            static_cast<int>(itProyectil->rect.h)
        };

        if (colisiona(rectProyectil, (*itObstaculo)->getRect())) {
            // Eliminar obstáculo
            delete *itObstaculo;
            itObstaculo = obstaculos.erase(itObstaculo);

            // Eliminar proyectil
            itProyectil = proyectiles.erase(itProyectil);
            Mix_PlayChannel(-1, objetoDest, 0);

            impacto = true;

            // Incrementar contador de obstáculos destruidos
            contadorObstaculosDestruidos++;

            // Revisar si se debe subir de nivel
            if (contadorObstaculosDestruidos >= obstaculosParaSubirNivel) {
                nivel++;
                velocidadObstaculos *= 1.25f; // Incrementar velocidad en 20%
                contadorObstaculosDestruidos = 0;
                obstaculosParaSubirNivel = obstaculosParaSubirNivel * 2;
                intervaloObstaculo *= 0.7f;

            }




            break; // Salir de este ciclo porque el proyectil ya se eliminó
        } else {
            ++itObstaculo;
        }
    }

    if (!impacto) {
        ++itProyectil;
    }
}

       


}

void Juego::render(Game* game) {

    if (mostrarControles) {

    fondo->setDestR(0, 0, 1800, 1200);
    fondo->Render();

        controles->setDestR(600, 300, 600, 600);
        controles->Render();
       

        return; // Mientras muestro controles, no renderizo el juego
    }

    
    
    

    SDL_Event event;
    SDL_PollEvent(&event);
    
    //fondo->setDestR(0, 0, 1800, 1200);
    fondo->Render();
    
    barco->setDestR(barcoX, barcoY, 160, 240);
    barco->Render();
    
    for (auto& obst : obstaculos) {
            obst->render();
        }

    for (auto& proyectil : proyectiles) {
        proyectil.render(game->getRenderer());
    }

    if (nivel >= 1 && nivel <= 5) {
    SDL_FRect rectNivel = {50.0f, 50.0f, 300.0f, 91.0f}; // Ajusta posición y tamaño

    SDL_RenderTexture(game->getRenderer(), nivelesTexturas[nivel - 1], NULL, &rectNivel);
}

    if (juegoPausado) {

        pausa->setDestR(302, 188, 1196, 825);
        pausa->Render();
        reanudar->setDestR(668,540,463,108);
        reanudar->Render();
        guardar->setDestR(543,700,713,108);
        guardar->Render();

    
    }
  
    
}

void Juego::onExit(Game* game) {

    for (auto& textura : nivelesTexturas) {
    SDL_DestroyTexture(textura);
    }
    nivelesTexturas.clear();

    
}
