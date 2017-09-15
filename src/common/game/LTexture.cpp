/*
 * LTexture.cpp
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */
#include "LTexture.h"

LTexture::LTexture(SDL_Renderer* renderer, float scale)
{
	//Initialize
	gRenderer = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	wasPlaced = false;
	tScale = scale;

}

LTexture::LTexture(SDL_Renderer* renderer,std::string path, float scale)
{
	//Initialize
	imagePath = path;
	gRenderer = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	wasPlaced = false;
	tScale = scale;

}
bool LTexture::loadImage(){
	return this->loadFromFile(imagePath);
}

LTexture::~LTexture(){
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path)
{
	//Get rid of preexisting texture
	free();

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
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}
void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render(SDL_Rect* clip, SDL_RendererFlip flip,int x,int y){
	 //Set rendering space and render to screen
	if(mTexture == NULL)
		this->loadImage();
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL )
	{ renderQuad.w = clip->w *tScale;
	renderQuad.h = clip->h *tScale; }
	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0.0, NULL, flip );
}
void LTexture::render(SDL_Rect* clip, SDL_RendererFlip flip){
	 //Set rendering space and render to screen
	if(mTexture == NULL)
		this->loadImage();
	SDL_Rect renderQuad = { x_pos, y_pos, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL )
	{ renderQuad.w = clip->w *tScale;
	renderQuad.h = clip->h *tScale; }
	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0.0, NULL, flip );
}
void LTexture::renderText( int x, int y)
{

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = x+100; // controls the width of the rect
	Message_rect.h = y+100; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(gRenderer, mTexture, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::setPosition(int x,int y){
	x_pos = x;
	y_pos = y;
	wasPlaced = true;
}
void LTexture::render()
{
	if(!wasPlaced)
		return;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x_pos, y_pos, mWidth * tScale, mHeight * tScale};

	//Set clip rendering dimensions
	/*if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}*/

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE );


}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

