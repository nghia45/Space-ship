#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Configs.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"

class Engine{
    public:
        bool init();
        void close();
        bool run();

        // init function
        bool initWindowAndRender();
        bool initShip(SDL_Renderer * &gRenderer);

        // init gameplay
        void closeGameplay();

        // load audio
        bool loadAudio();

        // load text fonts
        bool loadTextFont();

        // init and handle bullet when fire
        bool initBullet(SDL_Renderer * &gRenderer, Bullet* &bullet);

        // init and handle asteroid
        bool initAsteroid(SDL_Renderer * &gRenderer, Asteroid* &asteroid);

        // high score
        void set_highscore(int highscore);
        int get_highscore();
    private:
        // window game and renderer to draw
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        SDL_Texture* background;
        SDL_Texture* menu_background;
        SDL_Texture* menu_instruction;
        SDL_Texture* menu_highscore;
        TTF_Font* scoreboardFont;
        TTF_Font* gameOverFont_0;
        TTF_Font* gameOverFont_1;
        TTF_Font* gameOverFont_2;
        TTF_Font* highscoreFont;
        LTexture gameOverText[3];
        LTexture gameOverScoreText;
        LTexture scoreboardText;
        LTexture scoreText;
        LTexture highscoreText;
        // the game's characters, map, etc.
        Ship* ship;
        std::vector<Bullet*> prvBulletLoad;
        std::vector<Asteroid*> prvAsteroidLoad;
        // score
        int score = 0;
};

#endif // ENGINE_H
