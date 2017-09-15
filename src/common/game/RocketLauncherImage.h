/*
 * RocketLauncherImage.h
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */

#ifndef ROCKETLAUNCHERIMAGE_H_
#define ROCKETLAUNCHERIMAGE_H_

#include "AnimationImage.h"

class RocketLauncherImage: public AnimationImage {
public:
	RocketLauncherImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~RocketLauncherImage();
};

#endif /* ROCKETLAUNCHERIMAGE_H_ */
