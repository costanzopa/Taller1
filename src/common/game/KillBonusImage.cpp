/*
 * KillBonusImage.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "KillBonusImage.h"

namespace std {

KillBonusImage::KillBonusImage(SDL_Renderer* renderer,float scale):AnimationImage()  {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BONUS_DIR,scale);
	this->setSprites();
}

void KillBonusImage::setSprites(){
	gSpriteClips[0].x = 432;
	gSpriteClips[0].y = 1651;
	gSpriteClips[0].w = 22;
	gSpriteClips[0].h = 19;
}

KillBonusImage::~KillBonusImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
