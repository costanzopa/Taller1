/*
 * SingleShotAmmoImage.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "SingleShotAmmoImage.h"

namespace std {

SingleShotAmmoImage::SingleShotAmmoImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BONUS_DIR,scale);
	this->setSprites();

}
void SingleShotAmmoImage::setSprites(){
	gSpriteClips[0].x = 513;
	gSpriteClips[0].y = 28;
	gSpriteClips[0].w = 32;
	gSpriteClips[0].h = 29;
}

SingleShotAmmoImage::~SingleShotAmmoImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
