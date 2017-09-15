/*
 * FlameShotImage.h
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */

#ifndef FLAMESHOTIMAGE_H_
#define FLAMESHOTIMAGE_H_

#include "AnimationImage.h"

class FlameShotImage: public AnimationImage {
public:
	FlameShotImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~FlameShotImage();
};

#endif /* FLAMESHOTIMAGE_H_ */
