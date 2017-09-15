/*
 * SingleShotAmmoImage.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_SINGLESHOTAMMOIMAGE_H_
#define SRC_COMMON_GAME_SINGLESHOTAMMOIMAGE_H_

#include "AnimationImage.h"

namespace std {

class SingleShotAmmoImage: public AnimationImage {
public:
	SingleShotAmmoImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~SingleShotAmmoImage();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_SINGLESHOTAMMOIMAGE_H_ */
