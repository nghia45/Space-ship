#include "OtherObject.h"

Bullet::Bullet(SDL_Renderer* &gRenderer) {

    this->loadMedia(gRenderer);
    // set the width and height of the Ship
    this->setHeight(this->bulletTexture.getHeight());
    this->setWidth(this->bulletTexture.getWidth());
    this->set_health(1);
    // set the first position to render the Ship
//    this->set_x(0);
//    this->set_y(0);

}

Bullet::~Bullet() {
    //Free texture if it exists
    this->bulletTexture.free();


    this->setWidth(0);
    this->setHeight(0);

}

void Bullet::set_x(int x) {
    this->x = x;
}

void Bullet::set_y(int y) {
    this->y = y;
}

int Bullet::get_x() {
    return this->x;
}

int Bullet::get_y() {
    return this->y;
}

bool Bullet::get_health() {
    return this->health;
}

void Bullet::set_health(int _health) {
    this->health = _health;
}

void Bullet::setWidth(int w) {
    this->bulletWidth = w;
}

void Bullet::setHeight(int h) {
    this->bulletHeight = h;
}

int Bullet::getWidth() {
    return this->bulletWidth;
}

int Bullet::getHeight() {
    return this->bulletHeight;
}

bool Bullet::loadMedia(SDL_Renderer* &gRenderer) {
    //Loading success flag
    bool success = true;
    this->bulletTexture.loadFromFile(this->bulletTexturePath, gRenderer);
    if (this->bulletTexture.get_mTexture() == NULL) {
        success = false;
        printf( "Failed to load texture image !\n" );
    }
    return success;
}

void Bullet::renderCurrent(SDL_Renderer *&gRenderer) {

    /*
    TODO: draw the Ship character annimated
    */

     //Clear screen
     //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
     //SDL_RenderClear( gRenderer );

    //Render texture to screen
    this->bulletTexture.render(gRenderer, this->get_x(), this->get_y());

    return;
}

void Bullet::fire() {
    if(this->health == 1) {
        x += BULLET_VELOCITY;

        //If the ship went too far to the left or right
        if( ( x < 0 ) || ( x + this->getWidth() > SCREEN_WIDTH ) )
        {
            this->set_health(0);
            this->~Bullet();
        }
    }
    return;
}
