# Spaceship
## First SDL2 game
- Using C++ with CodeBlock and SDL2
## Main game stucture 
- Engine: Cointain all character, background. Control the game loop, collect all charactor states and handle these.
By these states, drawing all to the screen.
- Ship: moving, firing, collision.
- Asteroids: generate randomly, fly from right to left, increase speed by time.
## Gameplay
- Player control the spaceship using the keyboard to go up, down, left, right and spacebar to fire. Asteroid will generate randomly and fly from the right of the screen to the left, disappear when hit the left border. Spaceship can fire to destroy asteroid, or dodge it, or else if it colide with an asteroid the game will be over. Highscore increase by time.
