#include "Engine.h"
#include "defines.h"
#include "Ship.h"
#include "LTexture.h"


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

bool Engine::initWindowAndRender() {

    // Initialization flag
    bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->gWindow = SDL_CreateWindow( "Space ship", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( this->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			this->gRenderer = SDL_CreateRenderer( this->gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( this->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Engine::initShip(SDL_Renderer * &gRenderer) {
    this->ship = new Ship(gRenderer);
    return true;
}

bool Engine::initBullet(SDL_Renderer * &gRenderer) {
    this->bullet = new Bullet(gRenderer);
    return true;
}


SDL_Texture* loadTexture( std::string path, SDL_Renderer* &gRenderer )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool Engine::init() {
    /*
    Init function that inits all window, render, and characters such as pacman, ghosts, map, etc
    */

    /*
    TODO: add success flag to check if initize success or not
    */

    this->initWindowAndRender();
    this->initShip(this->gRenderer);
    this->background = loadTexture("assert/background.jpg", gRenderer);
    return true;
}

void Engine::close() {

	//Free ship
	//this->ship->free();
    delete(this->ship);
	//Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

    return;
}


bool Engine::run() {
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    // Game loop. This contain game action
    while( !quit )
    {
        //Handle events on queue and check when user decided to quit game
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if( e.type == SDL_KEYDOWN) if(e.key.keysym.sym == SDLK_ESCAPE) quit = true;

			// Handle event for ship control
			this->ship->handleEvent(e);
			if( e.type == SDL_KEYDOWN) if(e.key.keysym.sym == SDLK_SPACE){
                this->initBullet(this->gRenderer);
                this->bullet->set_x(this->ship->get_x() + 45 );
                this->bullet->set_y(this->ship->get_y() + 10  );
            }
        }
        /*
        TODO: add game logic in here
        */

        /*
        Note that we define render in each object as this function, and in engine, we check the state of each
        object and call this render function to draw on the screen
        */

	   	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		SDL_RenderCopy( gRenderer, background, NULL, NULL );

		this->ship->move();

        // First, just render the character
        this->ship->renderCurrent(this->gRenderer);

        if(bullet != NULL){
            this->bullet->fire();
            this->bullet->renderCurrent(this->gRenderer);
            if(this->bullet->get_health() == 0){
                delete(this->bullet);
                bullet = NULL;
            }
        }
		SDL_RenderPresent(gRenderer);
		SDL_Delay(50);
    }

    // End game and free the memory
    this->close();

    return true;
}

