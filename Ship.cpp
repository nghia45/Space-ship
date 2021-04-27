#include "Ship.h"

using namespace std;

Ship::Ship(SDL_Renderer* &gRenderer) {

    this->loadMedia(gRenderer);
    // set the width and height of the Ship
    this->setHeight(this->shipTexture.getHeight());
    this->setWidth(this->shipTexture.getWidth());
    // set the first position to render the Ship
    this->set_x(100);
    this->set_y(SCREEN_HEIGHT/3);
    this->set_health(1);
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

void Ship::set_velocity(int velocity) {
    this->x_velocity = velocity;
    this->y_velocity = velocity;
}

void Ship::set_angle(int angle){
    this->angle = angle;
}

int Ship::getWidth() {
    return this->shipWidth;
}

int Ship::getHeight() {
    return this->shipHeight;
}

int Ship::getVelocity() {
    return SHIP_VELOCITY;
}

int Ship::get_x() {
    return this->x;
}

int Ship::get_y() {
    return this->y;
}

bool Ship::get_health() {
    return this->health;
}

void Ship::set_health(int _health) {
    this->health = _health;
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
    //Render texture to screen
    this->shipTexture.render(gRenderer, this->get_x(), this->get_y(), NULL, angle);

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
            case SDLK_UP:
                angle -= 20;
                y_velocity -= SHIP_VELOCITY;  break;
            case SDLK_DOWN:
                angle += 20;
                y_velocity += SHIP_VELOCITY;  break;
            case SDLK_LEFT: x_velocity -= SHIP_VELOCITY;  break;
            case SDLK_RIGHT: x_velocity += SHIP_VELOCITY;  break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                angle += 20;
                y_velocity += SHIP_VELOCITY; break;
            case SDLK_DOWN:
                angle -= 20;
                y_velocity -= SHIP_VELOCITY; break;
            case SDLK_LEFT: x_velocity += SHIP_VELOCITY; break;
            case SDLK_RIGHT: x_velocity -= SHIP_VELOCITY; break;
        }
    }
}

void Ship::move()
{
    //Move the ship left or right
    x += x_velocity;

    //If the ship went too far to the left or right
    if( ( x < 0 ) || ( x + this->getWidth() > SCREEN_WIDTH ) )
    {
        //Move back
        x -= x_velocity;
    }

    //Move the ship up or down
    y += y_velocity;

    //If the ship went too far up or down
    if( ( y < 0 ) || ( y + this->getHeight() > SCREEN_HEIGHT ) )
    {
        //Move back
        y -= y_velocity;
    }
}

bool Ship::checkColision(const SDL_Rect rect){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of ship
    leftA = this->get_x();
    rightA = this->get_x() + this->getWidth();
    topA = this->get_y();
    bottomA = this->get_y() + this->getHeight();

    //Calculate the sides of rect
    leftB = rect.x;
    rightB = rect.x + rect.w;
    topB = rect.y;
    bottomB = rect.y + rect.h;
    //If any of the sides from ship are outside of rect
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from ship are outside of rect
    return true;
}

