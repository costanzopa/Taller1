/*
 * BigEyesLaserImage.cpp
 *
 *  Created on: 21/11/2016
 *      Author: usuario
 */

#include "BigEyesLaserImage.h"

BigEyesLaserImage::BigEyesLaserImage(SDL_Renderer* renderer,float scale):AnimationImage()  {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::ENEMY_EYES,scale);
	this->setSprites();

}
void BigEyesLaserImage::setSprites(){
	gSpriteClips[0].x = 363;
	gSpriteClips[0].y = 145;
	gSpriteClips[0].w = 11;
	gSpriteClips[0].h = 12;

	gSpriteClips[1].x = 391;
	gSpriteClips[1].y = 146;
	gSpriteClips[1].w = 12;
	gSpriteClips[1].h = 11;

	gSpriteClips[2].x = 377;
	gSpriteClips[2].y = 146;
	gSpriteClips[2].w = 11;
	gSpriteClips[2].h = 10;

	gSpriteClips[3].x = 406;
	gSpriteClips[3].y = 146;
	gSpriteClips[3].w = 10;
	gSpriteClips[3].h = 11;

	gSpriteClips[4].x = 363;
	gSpriteClips[4].y = 160;
	gSpriteClips[4].w = 11;
	gSpriteClips[4].h = 12;

	gSpriteClips[5].x = 377;
	gSpriteClips[5].y = 132;
	gSpriteClips[5].w = 11;
	gSpriteClips[5].h = 10;

	gSpriteClips[6].x = 391;
	gSpriteClips[6].y = 161;
	gSpriteClips[6].w = 12;
	gSpriteClips[6].h = 11;

	gSpriteClips[7].x = 406;
	gSpriteClips[7].y = 161;
	gSpriteClips[7].w = 10;
	gSpriteClips[7].h = 11;

	gSpriteClips[8].x = 224;
	gSpriteClips[8].y = 150;
	gSpriteClips[8].w = 17;
	gSpriteClips[8].h = 17;

	gSpriteClips[9].x = 244;
	gSpriteClips[9].y = 148;
	gSpriteClips[9].w = 21;
	gSpriteClips[9].h = 21;

	gSpriteClips[10].x = 268;
	gSpriteClips[10].y = 146;
	gSpriteClips[10].w = 25;
	gSpriteClips[10].h = 25;

	gSpriteClips[11].x = 296;
	gSpriteClips[11].y = 144;
	gSpriteClips[11].w = 29;
	gSpriteClips[11].h = 29;

	gSpriteClips[12].x = 329;
	gSpriteClips[12].y = 143;
	gSpriteClips[12].w = 31;
	gSpriteClips[12].h = 31;
}
BigEyesLaserImage::~BigEyesLaserImage() {
	// TODO Auto-generated destructor stub
}

