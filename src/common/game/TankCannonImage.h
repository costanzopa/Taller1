/*
 * TankCannonImage.h
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#ifndef TANKCANNONIMAGE_H_
#define TANKCANNONIMAGE_H_

#include "AnimationImage.h"

class TankCannonImage: public AnimationImage {
public:
	TankCannonImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~TankCannonImage();
};

#endif /* TANKCANNONIMAGE_H_ */
