#include "Engine.h"

int main(int argc, char* args[]) {
    Engine *engine = new Engine();

    // init the engine for running game
    engine->init();

    // run the game
    engine->run();

    return 0;
}
