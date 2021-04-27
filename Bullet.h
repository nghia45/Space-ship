#ifndef BULLET_H
#define BULLET_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "LTexture.h"
#include "Configs.h"

class Bullet
{
    public:
    Bullet(SDL_Renderer* &gRenderer);
    ~Bullet();

    void set_x(int x);
    void set_y(int y);
    void setWidth(int w);
    void setHeight(int h);
    int getWidth();
    int getHeight();
    void set_health(int health);
    bool get_health();
    int get_x();
    int get_y();

    void fire();
    bool checkColision(const SDL_Rect rect);

    void renderCurrent(SDL_Renderer* &gRenderer);
    bool loadMedia(SDL_Renderer* &gRenderer);

	LTexture bulletTexture;
	std::string bulletTexturePath  = "assert/bullet.png";
	//SDL_Texture *texture;
	private:
    int bulletWidth;
    int bulletHeight;
    int x;
	int y;
	int health;
};

#endif // BULLET_H
