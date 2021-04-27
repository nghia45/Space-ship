#include"Asteroid.h"

#include <cstdlib>
#include <ctime>

Asteroid::Asteroid(SDL_Renderer* &gRenderer) {

    this->loadMedia(gRenderer);
    // set the width and height of the Asteroid
    this->setHeight(this->asteroidTexture.getHeight());
    this->setWidth(this->asteroidTexture.getWidth());
    this->set_health(1);
    // set the first position to render the Asteroid
    this->set_x(SCREEN_WIDTH);
	int res = rand() % (SCREEN_HEIGHT - 100) ;
    this->set_y(res);
    this->setRect(this->get_x(), this->get_y(), this->getHeight(), this->getWidth());
}

Asteroid::~Asteroid() {
    //Free texture if it exists
    this->asteroidTexture.free();

    this->setWidth(0);
    this->setHeight(0);
    this->angle = 0;
}

void Asteroid::set_x(int x) {
    this->x = x;
}

void Asteroid::set_y(int y) {
    this->y = y;
}

int Asteroid::get_x() {
    return this->x;
}

int Asteroid::get_y() {
    return this->y;
}

bool Asteroid::get_health() {
    return this->health;
}

void Asteroid::set_health(int _health) {
    this->health = _health;
}

void Asteroid::setWidth(int w) {
    this->asteroidWidth = w;
}

void Asteroid::setHeight(int h) {
    this->asteroidHeight = h;
}

void Asteroid::setRect(int x, int y, int w, int h) {
    this->asteroidCollider.x = x ;
    this->asteroidCollider.y = y ;
    this->asteroidCollider.w = w ;
    this->asteroidCollider.h = h ;
}

int Asteroid::getWidth() {
    return this->asteroidWidth;
}

int Asteroid::getHeight() {
    return this->asteroidHeight;
}


void Asteroid::set_velocity(int velocity) {
    this->asteroid_velocity = velocity;
}

SDL_Rect Asteroid::get_Rect(){
    return this->asteroidCollider;
}

bool Asteroid::loadMedia(SDL_Renderer* &gRenderer) {
    //Load sprite sheet texture
    bool success = true;
    int asteroidType = rand() % 10 ;
    this->asteroidTexture.loadFromFile(this->asteroidTexturePath[asteroidType], gRenderer);
    if (this->asteroidTexture.get_mTexture() == NULL) {
        success = false;
        printf( "Failed to load texture image !\n" );
    }
    return success;
}

void Asteroid::renderCurrent(SDL_Renderer *&gRenderer) {

    /*
    TODO: draw the Ship character annimated
    */

     //Clear screen
     //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
     //SDL_RenderClear( gRenderer );

    //Render texture to screen
    this->asteroidTexture.render(gRenderer, this->get_x(), this->get_y(), NULL, angle);

    return;
}

void Asteroid::move() {
    if(this->health == 1) {
        this->x -= asteroid_velocity;
        this->setRect(x,y,asteroidWidth,asteroidHeight);
        //If the asteroid went too far to the left or right
        if( x < 0 )
        {
            this->set_health(0);
            this->~Asteroid();
        }
    }
    this->angle -= 2;
    return;
}
