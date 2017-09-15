/*
 * RocketAmmoImage.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_ROCKETAMMOIMAGE_H_
#define SRC_COMMON_GAME_ROCKETAMMOIMAGE_H_

#include "AnimationImage.h"

namespace std {

class RocketAmmoImage: public AnimationImage {
public:
	RocketAmmoImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~RocketAmmoImage();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_ROCKETAMMOIMAGE_H_ */
