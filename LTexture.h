#ifndef L_TEXTURE_H
#define L_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile( std::string path, SDL_Renderer* &gRenderer);
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( SDL_Renderer* &gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();
		SDL_Texture* get_mTexture();

	private:
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


#endif
