/*
 * RocketAmmoImage.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "RocketAmmoImage.h"

namespace std {

RocketAmmoImage::RocketAmmoImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BONUS_DIR,scale);
	this->setSprites();

}
void RocketAmmoImage::setSprites(){
	gSpriteClips[0].x = 203;
	gSpriteClips[0].y = 29;
	gSpriteClips[0].w = 32;
	gSpriteClips[0].h = 29;
}


RocketAmmoImage::~RocketAmmoImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
