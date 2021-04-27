#ifndef ASTEROID_H
#define ASTEROID_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "LTexture.h"
#include "Configs.h"

class Asteroid
{
    public:
    Asteroid(SDL_Renderer* &gRenderer);
    ~Asteroid();

    void set_x(int x);
    void set_y(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setRect(int x, int y, int w, int h);
    void set_velocity(int velocity);
    void set_health(int health);
    int getWidth();
    int getHeight();
    bool get_health();
    int get_x();
    int get_y();
    SDL_Rect get_Rect();

    void move();

    void renderCurrent(SDL_Renderer* &gRenderer);
    bool loadMedia(SDL_Renderer* &gRenderer);

	LTexture asteroidTexture;
    std::string asteroidTexturePath[10] = {
        "assert/Asteroids/bAsteroid1.png",
        "assert/Asteroids/bAsteroid2.png",
        "assert/Asteroids/bAsteroid3.png",
        "assert/Asteroids/mAsteroid1.png",
        "assert/Asteroids/mAsteroid2.png",
        "assert/Asteroids/mAsteroid3.png",
        "assert/Asteroids/mAsteroid4.png",
        "assert/Asteroids/sAsteroid1.png",
        "assert/Asteroids/sAsteroid2.png",
        "assert/Asteroids/sAsteroid3.png"
    };
	//SDL_Texture *texture;
	private:
    int asteroid_velocity;
    int asteroidWidth;
    int asteroidHeight;
    int x;
	int y;
	int health;
	int angle = 0;
	SDL_Rect asteroidCollider;
};


#endif // ASTEROID_H
