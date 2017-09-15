/*
 * SingleShotImage.cpp
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */

#include "SingleShotImage.h"

SingleShotImage::SingleShotImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BULLETS_DIR,scale);
	this->setSprites();
}
void SingleShotImage::setSprites(){
	gSpriteClips[0].x = 22;
	gSpriteClips[0].y = 65;
	gSpriteClips[0].w = 16;
	gSpriteClips[0].h = 19;

	gSpriteClips[1].x = 205;
	gSpriteClips[1].y = 347;
	gSpriteClips[1].w = 17;
	gSpriteClips[1].h = 21;

	gSpriteClips[2].x = 224;
	gSpriteClips[2].y = 345;
	gSpriteClips[2].w = 17;
	gSpriteClips[2].h = 23;

	gSpriteClips[3].x = 243;
	gSpriteClips[3].y = 346;
	gSpriteClips[3].w = 17;
	gSpriteClips[3].h = 21;

	gSpriteClips[4].x = 262;
	gSpriteClips[4].y = 344;
	gSpriteClips[4].w = 17;
	gSpriteClips[4].h = 23;

	gSpriteClips[5].x = 280;
	gSpriteClips[5].y = 344;
	gSpriteClips[5].w = 17;
	gSpriteClips[5].h = 22;

}
SingleShotImage::~SingleShotImage() {
	// TODO Auto-generated destructor stub
}

