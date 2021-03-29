#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Engine.h"

using namespace std;


int main(int argc, char* args[]) {
    Engine *engine = new Engine();

    // init the engine for running game
    engine->init();

    // run the game
    engine->run();

    return 0;
}
