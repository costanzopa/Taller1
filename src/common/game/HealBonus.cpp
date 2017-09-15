/*
 * HealBonus.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "HealBonus.h"

namespace std {

HealBonus::HealBonus(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BONUS_DIR,scale);
	this->setSprites();

}

void HealBonus::setSprites(){
	gSpriteClips[0].x = 13;
	gSpriteClips[0].y = 336;
	gSpriteClips[0].w = 26;
	gSpriteClips[0].h = 17;
}

HealBonus::~HealBonus() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
