/*
 * BigEyesBombImage.cpp
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#include "BigEyesBombImage.h"

BigEyesBombImage::BigEyesBombImage(SDL_Renderer* renderer,float scale) {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::ENEMY_EYES,scale);
	this->setSprites();

}
void BigEyesBombImage::setSprites(){
	gSpriteClips[0].x = 21;
	gSpriteClips[0].y = 196;
	gSpriteClips[0].w = 12;
	gSpriteClips[0].h = 25;

	gSpriteClips[1].x = 48;
	gSpriteClips[1].y = 194;
	gSpriteClips[1].w = 31;
	gSpriteClips[1].h = 29;

	gSpriteClips[2].x = 84;
	gSpriteClips[2].y = 194;
	gSpriteClips[2].w = 29;
	gSpriteClips[2].h = 29;

	gSpriteClips[3].x = 96;
	gSpriteClips[3].y = 499;
	gSpriteClips[3].w = 35;
	gSpriteClips[3].h = 24;

	gSpriteClips[4].x = 118;
	gSpriteClips[4].y = 189;
	gSpriteClips[4].w = 28;
	gSpriteClips[4].h = 35;

	gSpriteClips[5].x = 158;
	gSpriteClips[5].y = 185;
	gSpriteClips[5].w = 27;
	gSpriteClips[5].h = 38;

	gSpriteClips[6].x = 202;
	gSpriteClips[6].y = 191;
	gSpriteClips[6].w = 22;
	gSpriteClips[6].h = 32;

	gSpriteClips[7].x = 242;
	gSpriteClips[7].y = 193;
	gSpriteClips[7].w = 17;
	gSpriteClips[7].h = 31;

	gSpriteClips[8].x = 279;
	gSpriteClips[8].y = 199;
	gSpriteClips[8].w = 14;
	gSpriteClips[8].h = 24;

	gSpriteClips[9].x = 310;
	gSpriteClips[9].y = 198;
	gSpriteClips[9].w = 9;
	gSpriteClips[9].h = 23;
}
BigEyesBombImage::~BigEyesBombImage() {
	// TODO Auto-generated destructor stub
}

