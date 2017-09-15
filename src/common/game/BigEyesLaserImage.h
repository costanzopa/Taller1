/*
 * BigEyesLaserImage.h
 *
 *  Created on: 21/11/2016
 *      Author: usuario
 */

#ifndef BIGEYESLASERIMAGE_H_
#define BIGEYESLASERIMAGE_H_

#include "AnimationImage.h"

class BigEyesLaserImage: public AnimationImage {
public:
	BigEyesLaserImage(SDL_Renderer* renderer,float scale);
	void setSprites();
	virtual ~BigEyesLaserImage();
};

#endif /* BIGEYESLASERIMAGE_H_ */
