/*
 * EnemyImage.h
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#ifndef ENEMYIMAGE_H_
#define ENEMYIMAGE_H_

#include <list>
#include <string>
#include "GameImage.h"

using namespace std;
class EnemyImage: public GameImage {

public:
	SDL_Rect* currentClip;
	SDL_RendererFlip flip;
	bool connected;
	bool renderedState;
	bool isDead;
	int lastState;
	EnemyImage(SDL_Renderer* renderer,std::string path, float scale);
	void dead(){ this->isDead= true;}
	void setStatus(int);
	virtual void render()=0;
	virtual void setFrameProperties(int)=0;
	virtual ~EnemyImage();
};

#endif /* ENEMYIMAGE_H_ */
