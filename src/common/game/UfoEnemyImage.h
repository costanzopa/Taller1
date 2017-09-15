/*
 * UfoEnemyImage.h
 *
 *  Created on: 5/11/2016
 *      Author: usuario
 */

#ifndef UFOENEMYIMAGE_H_
#define UFOENEMYIMAGE_H_
#define UFOENEMY_FRAMES 12
#define UFOLIGHT_FRAMES 10
#include "LTexture.h"
#include <string>
#include "BossImage.h"

namespace std {

class UfoEnemyImage:public BossImage{
public:
	SDL_Rect gSpriteClips[ UFOENEMY_FRAMES ];

	SDL_Rect gLightClips[ UFOLIGHT_FRAMES ];
	SDL_Rect* currentLightsClip;

	LTexture* lights;


	//Initializes variables
	UfoEnemyImage(SDL_Renderer* renderer,std::string path, float scale);

	//Deallocates memory
	virtual ~UfoEnemyImage();
	virtual void setMainFrame(int);
	virtual void setExtraFrame(int);
	virtual void setPosition(int x,int y);
	void changeImageState();
	//Renders texture at given point
	virtual void render();
	void setStatus(int frame,int connection);
private:
	void setSprites();
	void setLightSprites();
	int getLightFrame(int frame);

};

} /* namespace std */


#endif /* UFOENEMYIMAGE_H_ */
