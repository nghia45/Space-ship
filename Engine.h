#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "defines.h"

#include "Ship.h"
#include "OtherObject.h"

class Engine{
    public:
        bool init();
        void close();
        bool run();

        // init function
        bool initWindowAndRender();
        bool initShip(SDL_Renderer * &gRenderer);

        // init bullet when fire
        bool initBullet(SDL_Renderer * &gRenderer);
    private:
        // window game and renderer to draw
        // the game's characters, map, etc.
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        SDL_Texture* background;
        Ship* ship;
        Bullet* bullet;
};

#endif // ENGINE_H
