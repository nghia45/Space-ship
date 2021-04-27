#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Engine.h"
#include "Configs.h"
#include "Ship.h"
#include "LTexture.h"

using namespace std;

int Engine::get_highscore(){
    int highscore;
    ifstream f;
    f.open("score.txt");
    if(f.is_open())
    {
        int num;
        while(!f.eof()){
            f>>num;
            highscore = num;
        }
    }
    f.close();
    return highscore;
}

void Engine::set_highscore(int highscore){
    ofstream f;
    f.open("score.txt");
    if(f.is_open()) f<<highscore;
    f.close();
}

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

bool Engine::initBullet(SDL_Renderer * &gRenderer, Bullet* &bullet) {
        bullet = new Bullet(gRenderer);
        prvBulletLoad.push_back(bullet);
    return true;
}

bool Engine::initAsteroid(SDL_Renderer * &gRenderer, Asteroid* &asteroid) {
        asteroid = new Asteroid(gRenderer);
        prvAsteroidLoad.push_back(asteroid);
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

bool Engine::loadAudio(){
    //Loading success flag
    bool success = true;


    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    else{
        //Load music
        startupMusic = Mix_LoadMUS( "assert/Audio/Star Wars Theme Song.mp3" );
        if( startupMusic == NULL )
        {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        //Load sound effects
        bulletSound = Mix_LoadWAV( "assert/Audio/layered-gunshot-6.wav" );
        if( bulletSound == NULL )
        {
            printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        explosionSound = Mix_LoadWAV( "assert/Audio/explosion-012.wav" );
        if( explosionSound == NULL )
        {
            printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        gameOverSound = Mix_LoadWAV( "assert/Audio/nhe.wav" );
        if( gameOverSound == NULL )
        {
            printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }
    return success;
}

bool Engine::loadTextFont() {
    // Loading success flag
    bool success = true;


    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else {
        //Open the font
        gameOverFont_1 = TTF_OpenFont( "assert/Font/StarcruiserExpandedSemiItalic-gKeY.ttf", 100 );
        if( gameOverFont_1 == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 255, 0, 0 };
            if( !this->gameOverText[0].loadFromRenderedText( "GAME OVER!", textColor, gRenderer, gameOverFont_1 ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
        gameOverFont_1 = TTF_OpenFont( "assert/Font/StarcruiserExpandedSemiItalic-gKeY.ttf", 60 );
        if( gameOverFont_1 == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 255, 255, 255 };
            if( !this->gameOverText[1].loadFromRenderedText( "Your score: ", textColor, gRenderer, gameOverFont_1 ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
        gameOverFont_2 = TTF_OpenFont("assert/Font/StarcruiserExpandedSemiItalic-gKeY.ttf", 42);
        if( gameOverFont_2 == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            SDL_Color textColor = {23, 74, 221};
            if( !this->gameOverText[2].loadFromRenderedText( "Returning to menu...", textColor, gRenderer, gameOverFont_2 ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
        scoreboardFont = TTF_OpenFont("assert/Font/LFAXD.ttf", 18);
        if( scoreboardFont == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            SDL_Color textColor = {255, 255, 255};
            if( !this->scoreboardText.loadFromRenderedText( "Score: ", textColor, gRenderer, scoreboardFont ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
        highscoreFont = TTF_OpenFont("assert/Font/LFAXD.ttf", 100);
        if( highscoreFont == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
    }
    return success;
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
    this->menu_background = loadTexture("assert/background - menu.jpg", gRenderer);
    this->menu_instruction = loadTexture("assert/background - instruction.jpg", gRenderer);
    this->menu_highscore = loadTexture("assert/background - highscore.jpg", gRenderer);
    this->background = loadTexture("assert/background.jpg", gRenderer);
    this->loadAudio();
    this->loadTextFont();
    return true;
}

void Engine::closeGameplay() {
    // Ship default
    this->ship->set_x(100);
    this->ship->set_y(SCREEN_HEIGHT/3);
    this->ship->set_velocity(0);
    this->ship->set_angle(0);
    // Delete remaining bullets
    if(prvBulletLoad.size() >= 0){
        for(int i = 0; i < prvBulletLoad.size(); i++){
            prvBulletLoad.erase(prvBulletLoad.begin() + i);
            prvBulletLoad[i]->set_health(0);
        }
    }
    // Delete remaining asteroid
    if(prvAsteroidLoad.size() >= 0){
        for(int i = 0; i < prvAsteroidLoad.size(); i++){
            prvAsteroidLoad.erase(prvAsteroidLoad.begin() + i);
            prvAsteroidLoad[i]->set_health(0);
        }
    }
    if(this->get_highscore() < score) this->set_highscore(score);
    score = 0;
    return;
}


void Engine::close() {

	//Free ship
    delete(this->ship);

	//Destroy window
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;

    //Free the music
    Mix_FreeMusic( startupMusic );
    startupMusic = NULL;

    Mix_FreeChunk( bulletSound );
    bulletSound = NULL;
    Mix_FreeChunk( explosionSound );
    explosionSound = NULL;
    Mix_FreeChunk( gameOverSound );
    gameOverSound = NULL;

    //Free global font
    TTF_CloseFont( gameOverFont_0 );
    gameOverFont_0 = NULL;
    TTF_CloseFont( gameOverFont_1);
    gameOverFont_1 = NULL;
    TTF_CloseFont( gameOverFont_2);
    gameOverFont_2 = NULL;
    TTF_CloseFont( scoreboardFont );
    scoreboardFont = NULL;
    TTF_CloseFont( highscoreFont );
    highscoreFont = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
    Mix_Quit();
    TTF_Quit();

    return;
}


bool Engine::run() {
    //Main loop flag
    bool quit = false;
    bool quit_game = true;
    //Event handler
    SDL_Event e;
    SDL_Texture* menu = menu_background;

    //Set random state
    srand(time(NULL));

    //Game mechanic elements
    int game_state;

    //Score mechanism elements

    // Game loop. This contain game action
    while( !quit )
    {
        //Music handle
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( startupMusic, -1 );
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		SDL_RenderCopy( gRenderer, menu, NULL, NULL );
		SDL_RenderPresent(gRenderer);

		while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            SDL_Color textcolor = {255,255,255};
            this->highscoreText.loadFromRenderedText(to_string(this->get_highscore()), textcolor, gRenderer, highscoreFont );
            if( e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_s:
                        quit_game = false;
                        break;
                    case SDLK_i:
                        menu = menu_instruction;
                        break;
                    case SDLK_h:
                        {
                        menu = menu_highscore;
                        this->highscoreText.render(gRenderer, 400, 400);
                        SDL_RenderPresent(gRenderer);
                        break;
                        }
                    case SDLK_m:
                        menu = menu_background;
                        break;
                 }
            }
		}
		while(!quit_game)
        {
            if(Mix_PlayingMusic) Mix_PauseMusic();
            // Score calculating mechanism
            if( score <= 20 ) game_state = 0;
            else if( score <= 50) game_state = 1;
            else if( score <= 100) game_state = 2;
            else if( score <= 300) game_state = 3;
            else if( score <= 1000) game_state = 4;

            //Handle events on queue and check when user decided to quit game
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit_game = true;
                }
                if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit_game = true;

                // Handle event for ship control and bullet fire
                this->ship->handleEvent(e);
                if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
                    if(prvBulletLoad.size() < MAX_BULLET_COUNT){
                        Bullet* pBullet = NULL;
                        initBullet(this->gRenderer, pBullet);
                        pBullet->set_x(this->ship->get_x() + 45 );
                        pBullet->set_y(this->ship->get_y() + 10 );
                        Mix_PlayChannel( -1, bulletSound, 0 );
                    }
                }
            }
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            SDL_RenderCopy( gRenderer, background, NULL, NULL );

            // Handle ship rendering
            this->ship->move();
            for(int j = 0; j < prvAsteroidLoad.size(); j++){
                if(this->ship->checkColision(prvAsteroidLoad[j]->get_Rect())){
                    ship->set_health(0);
                    //prvAsteroidLoad[j]->set_health(0);
                    Mix_PlayChannel( -1, gameOverSound, 0 );
                    quit_game = true;
                    SDL_Delay(1000);
                    this->gameOverText[0].render(gRenderer, 250, 200);
                    this->gameOverText[1].render(gRenderer, 330, 320);
                    SDL_Color textcolor = {255,255,255};
                    this->gameOverScoreText.loadFromRenderedText(to_string(score), textcolor, gRenderer, gameOverFont_1);
                    this->gameOverScoreText.render(gRenderer, 850, 320);
                    this->gameOverText[2].render(gRenderer, 350, 500);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(3000);
                }
            }
            this->ship->renderCurrent(this->gRenderer);

            // Handle bullets rendering
            if(prvBulletLoad.size() >= 0){
                for(int i = 0; i < prvBulletLoad.size(); i++){
                    if(prvBulletLoad[i] != NULL){
                        this->prvBulletLoad[i]->fire();
                        this->prvBulletLoad[i]->renderCurrent(this->gRenderer);
                        for(int j = 0; j < prvAsteroidLoad.size(); j++){
                            if(prvAsteroidLoad[j] != NULL){
                                if(prvBulletLoad[i]->checkColision(prvAsteroidLoad[j]->get_Rect())){
                                    prvBulletLoad[i]->set_health(0);
                                    prvAsteroidLoad[j]->set_health(0);
                                    Mix_PlayChannel( -1, explosionSound, 0 );
                                }
                            }
                        }
                        if(this->prvBulletLoad[i]->get_health() == 0){
                            prvBulletLoad.erase(prvBulletLoad.begin() + i);
                        }
                    }
                }
            }

            // Handle asteroids rendering
            if(rand() % ASTEROID_FREQUENCY[game_state] == 0){
                bool base_asteroid_flag =  score <= 20 && prvAsteroidLoad.size() < 5 ;
                if( base_asteroid_flag || score > 20 ){
                    Asteroid* pAsteroid = NULL;
                    initAsteroid(this->gRenderer, pAsteroid);
                    pAsteroid->set_velocity(ASTEROID_VELOCITY[game_state]);
                }
            }

            if(prvAsteroidLoad.size() >= 0){
                for(int i = 0; i < prvAsteroidLoad.size(); i++){
                    if(prvAsteroidLoad[i] != NULL){
                        this->prvAsteroidLoad[i]->move();
                        this->prvAsteroidLoad[i]->renderCurrent(this->gRenderer);
                        if(this->prvAsteroidLoad[i]->get_health() == 0){
                            prvAsteroidLoad.erase(prvAsteroidLoad.begin() + i);
                            score += 5;
                            cout<<"Score: "<<score<<endl;
                        }
                    }
                }
            }
        // Display scoreboard
        scoreboardText.render(gRenderer, 10, 10);
        SDL_Color textColor = {255, 255, 255};
        this->scoreText.loadFromRenderedText( to_string(this->score) , textColor, gRenderer, scoreboardFont );
        scoreText.render(gRenderer, 80, 10);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(50);
        }
        this->closeGameplay();
    }

    // End game and free the memory
    this->close();

    return true;
}
