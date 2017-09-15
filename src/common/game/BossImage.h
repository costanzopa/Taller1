/*
 * BossImage.h
 *
 *  Created on: 21/11/2016
 *      Author: usuario
 */

#ifndef BOSSIMAGE_H_
#define BOSSIMAGE_H_

#include "GameImage.h"
#include <list>
#include <string>

using namespace std;
class BossImage: public GameImage {
public:
	SDL_Rect* currentClip;
	SDL_RendererFlip flip;
	bool connected;
	bool renderedState;
	bool isDead;
	int lastState;
	BossImage(SDL_Renderer* renderer,std::string path, float scale);
	void dead(){ this->isDead= true;}
	virtual void setMainFrame(int)=0;
	virtual void setExtraFrame(int)=0;
	virtual ~BossImage();
};

#endif /* BOSSIMAGE_H_ */
