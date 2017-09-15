/*
 * FlameAmmoImage.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "FlameAmmoImage.h"

namespace std {

FlameAmmoImage::FlameAmmoImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BONUS_DIR,scale);
	this->setSprites();

}
void FlameAmmoImage::setSprites(){
	gSpriteClips[0].x = 284;
	gSpriteClips[0].y = 191;
	gSpriteClips[0].w = 31;
	gSpriteClips[0].h = 26;
}

FlameAmmoImage::~FlameAmmoImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
