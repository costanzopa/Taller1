/*
 * RocketLauncherImage.cpp
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */

#include "RocketLauncherImage.h"

RocketLauncherImage::RocketLauncherImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BULLETS_DIR,scale);
	this->setSprites();

}
void RocketLauncherImage::setSprites(){

	//Rocket

	gSpriteClips[0].x = 4;
	gSpriteClips[0].y = 242;
	gSpriteClips[0].w = 59;
	gSpriteClips[0].h = 15;

	gSpriteClips[1].x = 65;
	gSpriteClips[1].y = 242;
	gSpriteClips[1].w = 51;
	gSpriteClips[1].h = 15;

	//Explosion

	gSpriteClips[2].x = 377;
	gSpriteClips[2].y = 494;
	gSpriteClips[2].w = 37;
	gSpriteClips[2].h = 32;

	gSpriteClips[3].x = 417;
	gSpriteClips[3].y = 494;
	gSpriteClips[3].w = 35;
	gSpriteClips[3].h = 32;

	gSpriteClips[4].x = 455;
	gSpriteClips[4].y = 493;
	gSpriteClips[4].w = 32;
	gSpriteClips[4].h = 33;

	gSpriteClips[5].x = 493;
	gSpriteClips[5].y = 493;
	gSpriteClips[5].w = 33;
	gSpriteClips[5].h = 33;

	gSpriteClips[6].x = 531;
	gSpriteClips[6].y = 493;
	gSpriteClips[6].w = 31;
	gSpriteClips[6].h = 33;

	gSpriteClips[7].x = 567;
	gSpriteClips[7].y = 493;
	gSpriteClips[7].w = 25;
	gSpriteClips[7].h = 33;

//Aca empieza a la izquierda

	gSpriteClips[8].x = 1149;
	gSpriteClips[8].y = 242;
	gSpriteClips[8].w = 59;
	gSpriteClips[8].h = 15;

	gSpriteClips[9].x = 1094;
	gSpriteClips[9].y = 242;
	gSpriteClips[9].w = 51;
	gSpriteClips[9].h = 15;

	gSpriteClips[10].x = 788;
	gSpriteClips[10].y = 494;
	gSpriteClips[10].w = 37;
	gSpriteClips[10].h = 32;

	gSpriteClips[11].x = 749;
	gSpriteClips[11].y = 494;
	gSpriteClips[11].w = 35;
	gSpriteClips[11].h = 32;

	gSpriteClips[12].x = 710;
	gSpriteClips[12].y = 493;
	gSpriteClips[12].w = 32;
	gSpriteClips[12].h = 33;

	gSpriteClips[13].x = 673;
	gSpriteClips[13].y = 493;
	gSpriteClips[13].w = 33;
	gSpriteClips[13].h = 33;

	gSpriteClips[14].x = 636;
	gSpriteClips[14].y = 493;
	gSpriteClips[14].w = 31;
	gSpriteClips[14].h = 33;

	gSpriteClips[15].x = 608;
	gSpriteClips[15].y = 493;
	gSpriteClips[15].w = 25;
	gSpriteClips[15].h = 33;
}
RocketLauncherImage::~RocketLauncherImage() {
	// TODO Auto-generated destructor stub
}

