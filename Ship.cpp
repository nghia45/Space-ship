#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(SDL_Renderer* &gRenderer) {

    this->loadMedia(gRenderer);
    // set the width and height of the Ship
    this->setHeight(this->shipTexture.getHeight());
    this->setWidth(this->shipTexture.getWidth());
    // set the first position to render the Ship
    this->set_x(100);
    this->set_y(100);

}

Ship::~Ship() {
    //Free texture if it exists
    this->shipTexture.free();


    this->setWidth(0);
    this->setHeight(0);

}

void Ship::set_x(int x) {
    this->x = x;
}

void Ship::set_y(int y) {
    this->y = y;
}

void Ship::setWidth(int w) {
    this->shipWidth = w;
}

void Ship::setHeight(int h) {
    this->shipHeight = h;
}

int Ship::getWidth() {
    return this->shipWidth;
}

int Ship::getHeight() {
    return this->shipHeight;
}

int Ship::getVelocity() {
    return this->VELOCITY;
}

int Ship::get_x() {
    return this->x;
}

int Ship::get_y() {
    return this->y;
}

bool Ship::loadMedia(SDL_Renderer* &gRenderer) {
    //Loading success flag
    bool success = true;
    this->shipTexture.loadFromFile(this->shipTexturePath, gRenderer);
    if (this->shipTexture.get_mTexture() == NULL) {
        success = false;
        printf( "Failed to load texture image !\n" );
    }
    return success;
}

void Ship::renderCurrent(SDL_Renderer *&gRenderer) {

    /*
    TODO: draw the Ship character annimated
    */

     //Clear screen
     //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
     //SDL_RenderClear( gRenderer );

    //Render texture to screen
    this->shipTexture.render(gRenderer, this->get_x(), this->get_y());

    return;
}


void Ship::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: y_velocity -= VELOCITY;  break;
            case SDLK_DOWN: y_velocity += VELOCITY;  break;
            case SDLK_LEFT: x_velocity -= VELOCITY;  break;
            case SDLK_RIGHT: x_velocity += VELOCITY;  break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: y_velocity += VELOCITY; break;
            case SDLK_DOWN: y_velocity -= VELOCITY; break;
            case SDLK_LEFT: x_velocity += VELOCITY; break;
            case SDLK_RIGHT: x_velocity -= VELOCITY; break;
        }
    }
}

void Ship::move()
{
    //Move the dot left or right
    this->x += this->x_velocity;

    //If the dot went too far to the left or right
    if( ( x < 0 ) || ( x + this->getWidth() > SCREEN_WIDTH ) )
    {
        //Move back
        x -= x_velocity;
    }

    //Move the dot up or down
    y += y_velocity;

    //If the dot went too far up or down
    if( ( y < 0 ) || ( y + this->getHeight() > SCREEN_HEIGHT ) )
    {
        //Move back
        y -= y_velocity;
    }
}
