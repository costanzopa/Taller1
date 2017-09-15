/*
 * BigEyesBombImage.h
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#ifndef BIGEYESBOMBIMAGE_H_
#define BIGEYESBOMBIMAGE_H_

#include "AnimationImage.h"

class BigEyesBombImage: public AnimationImage {
public:
	BigEyesBombImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~BigEyesBombImage();
};

#endif /* BIGEYESBOMBIMAGE_H_ */
