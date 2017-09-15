/*
 * EyesEnemyImage.h
 *
 *  Created on: Nov 20, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_EYESENEMYIMAGE_H_
#define SRC_COMMON_GAME_EYESENEMYIMAGE_H_

#define EYESENEMY_FRAMES 18
#define EYESLASER_FRAMES 10

#include "BossImage.h"

namespace std {

class EyesEnemyImage: public BossImage {
public:
	SDL_Rect gSpriteClips[ EYESENEMY_FRAMES ];

	SDL_Rect gLaserClips[ EYESLASER_FRAMES ];
	SDL_Rect* currentLaserClip;

	LTexture* laser;

	EyesEnemyImage(SDL_Renderer* renderer,std::string path, float scale);
	virtual ~EyesEnemyImage();
	virtual void setMainFrame(int);
	virtual void setExtraFrame(int);
	virtual void setPosition(int x,int y);
	void changeImageState();
	//Renders texture at given point
	virtual void render();
	void setStatus(int frame,int connection);
private:
	void setSprites();
	void setLaserSprites();
	int getLightFrame(int frame);
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_EYESENEMYIMAGE_H_ */
