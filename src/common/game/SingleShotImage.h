/*
 * SingleShotImage.h
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */


#ifndef SINGLESHOTIMAGE_H_
#define SINGLESHOTIMAGE_H_
#include "AnimationImage.h"

class SingleShotImage: public AnimationImage {
public:
	SingleShotImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~SingleShotImage();
};

#endif /* SINGLESHOTIMAGE_H_ */
