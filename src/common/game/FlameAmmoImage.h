/*
 * FlameAmmoImage.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_FLAMEAMMOIMAGE_H_
#define SRC_COMMON_GAME_FLAMEAMMOIMAGE_H_

#include "AnimationImage.h"

namespace std {

class FlameAmmoImage: public AnimationImage {
public:
	FlameAmmoImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~FlameAmmoImage();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_FLAMEAMMOIMAGE_H_ */
