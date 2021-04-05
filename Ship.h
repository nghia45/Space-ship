#ifndef SHIP_H
#define SHIP_H

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "LTexture.h"
#include "defines.h"

using namespace std;

class Ship{
    public:
        Ship(SDL_Renderer* &gRenderer);
        ~Ship();

        void setWidth(int w);
        void setHeight(int h);
        void setVelocity(int v);
        void set_x(int x);
        void set_y(int y);
        int getWidth();
        int getHeight();
        int getVelocity();
        int get_x();
        int get_y();

        void handleEvent( SDL_Event& e );
		void move();

        void renderCurrent(SDL_Renderer* &gRenderer);
        bool loadMedia(SDL_Renderer* &gRenderer);

        // Using class LTexture
        LTexture shipTexture;
        string shipTexturePath  = "assert/spaceship.png";

    private:
        // SDL_Texture *pacmanTexture;
        int shipWidth;
        int shipHeight;
        //int state;
        const int VELOCITY = 10;

        int x_velocity = 0;
        int y_velocity = 0;
        int x;
        int y;
        int angle = 0;
};


#endif // SHIP_H
