/*
 * LTexture.h
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */

#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

using namespace std;

class LTexture{
	public:
		//Initializes variables
		LTexture(SDL_Renderer* renderer,std::string, float scale);

		LTexture(SDL_Renderer* renderer, float scale);

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Load From File wrapper
		bool loadImage();

		//Creates image from font string
		bool loadFromRenderedText(std::string,SDL_Color);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render();
		void setPosition(int x,int y);
		void render( SDL_Rect* clip, SDL_RendererFlip flip );
		void render( SDL_Rect* clip, SDL_RendererFlip flip ,int x,int y);
		void renderText(int x,int y);
		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		std::string imagePath;

		//Globally used font
		TTF_Font *gFont = NULL;
		//If it was placed on the screen already
		bool wasPlaced;
		//Image dimensions
		int mWidth;
		int mHeight;
		int x_pos;
		int y_pos;
		float tScale;
		SDL_Renderer* gRenderer;
};


#endif /* LTEXTURE_H_ */
