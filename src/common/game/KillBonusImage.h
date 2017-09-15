/*
 * KillBonusImage.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_KILLBONUSIMAGE_H_
#define SRC_COMMON_GAME_KILLBONUSIMAGE_H_

#include "AnimationImage.h"

namespace std {

class KillBonusImage: public AnimationImage {
public:
	KillBonusImage(SDL_Renderer*,float);
	void setSprites();
	virtual ~KillBonusImage();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_KILLBONUSIMAGE_H_ */
