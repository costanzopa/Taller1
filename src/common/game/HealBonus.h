/*
 * HealBonus.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_COMMON_GAME_HEALBONUS_H_
#define SRC_COMMON_GAME_HEALBONUS_H_

#include "AnimationImage.h"

namespace std {

class HealBonus: public AnimationImage {
public:
	HealBonus(SDL_Renderer*,float);
	void setSprites();
	virtual ~HealBonus();
};

} /* namespace std */

#endif /* SRC_COMMON_GAME_HEALBONUS_H_ */
