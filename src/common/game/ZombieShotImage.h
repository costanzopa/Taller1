/*
 * ZombieShot.h
 *
 *  Created on: 12/11/2016
 *      Author: usuario
 */

#ifndef ZOMBIESHOTIMAGE_H_
#define ZOMBIESHOTIMAGE_H_

#include "AnimationImage.h"

class ZombieShotImage: public AnimationImage {
public:
	ZombieShotImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~ZombieShotImage();
};

#endif /* ZOMBIESHOT_H_ */
