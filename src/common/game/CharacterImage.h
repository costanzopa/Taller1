/*
 * CharacterImage.h
 *
 *  Created on: 25/09/2016
 *      Author: guido
 */

#ifndef CHARACTERIMAGE_H_
#define CHARACTERIMAGE_H_
#define ANIMATION_FRAMES 340
#define LEG_FRAMES 40
#include "LTexture.h"
#include <string>
#include "GameImage.h"

using namespace std;

class CharacterImage: public GameImage{
public:
	SDL_Rect gSpriteClips[ ANIMATION_FRAMES ];
	SDL_Rect* currentClip;

	SDL_Rect gLegClips[ LEG_FRAMES ];
	SDL_Rect* currentLegClip;

	LTexture* legs;

	bool connected;
	bool renderedState;
	bool isDead;
	bool goingLeft;
	int lastState;
	int offset;
	//Initializes variables
	CharacterImage(SDL_Renderer* renderer,std::string path, float scale);

	//Deallocates memory
	~CharacterImage();
	void setFrameProperties(int);
	void setLegFrameProperties(int);

	void changeImageState();
	void changeLegsState();
	void setPosition(int,int);
	void dead(){this->isDead = true;}
	//Renders texture at given point
	virtual void render();
	void setLegStatus(int legNumber);
	void setStatus(int frame,int connection);
private:
	void setSprites();
	void setLegSprites();
	void setOffset(int);

};


#endif /* CHARACTERIMAGE_H_ */
