#ifndef DEFINES_H
#define DEFINES_H

#include <SDL_mixer.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SHIP_VELOCITY 10;
#define BULLET_VELOCITY 20;

const int MAX_BULLET_COUNT = 3;

const int SLOW_ASTEROID_VELOCITY = 7;
const int MEDIUM_ASTEROID_VELOCITY = 20;
const int FAST_ASTEROID_VELOCITY = 35;
const int SUPER_FAST_ASTEROID_VELOCITY = 50;
const int EXTRA_SUPER_FAST_ASTEROID_VELOCITY = 60;

const int ASTEROID_VELOCITY[5] = {SLOW_ASTEROID_VELOCITY, MEDIUM_ASTEROID_VELOCITY, FAST_ASTEROID_VELOCITY,
                                    SUPER_FAST_ASTEROID_VELOCITY, EXTRA_SUPER_FAST_ASTEROID_VELOCITY};

const int SLOW_ASTEROID_FREQUENCY = 5;
const int MEDIUM_ASTEROID_FREQUENCY = 30;
const int FAST_ASTEROID_FREQUENCY = 10;
const int SUPER_FAST_ASTEROID_FREQUENCY = 5;
const int EXTRA_SUPER_FAST_ASTEROID_FREQUENCY = 3;

const int ASTEROID_FREQUENCY[5] = {SLOW_ASTEROID_FREQUENCY, MEDIUM_ASTEROID_FREQUENCY, FAST_ASTEROID_FREQUENCY,
                                    SUPER_FAST_ASTEROID_FREQUENCY, EXTRA_SUPER_FAST_ASTEROID_FREQUENCY};

static Mix_Music *startupMusic = NULL;

static Mix_Chunk *bulletSound = NULL;
static Mix_Chunk *explosionSound = NULL;
static Mix_Chunk *gameOverSound = NULL;



#endif // DEFINES_H
