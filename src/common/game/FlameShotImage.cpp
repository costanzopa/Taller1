/*
 * FlameShotImage.cpp
 *
 *  Created on: 10/11/2016
 *      Author: usuario
 */

#include "FlameShotImage.h"

FlameShotImage::FlameShotImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::BULLETS_DIR,scale);
	this->setSprites();
}
void FlameShotImage::setSprites(){
	gSpriteClips[0].x = 4;
	gSpriteClips[0].y = 505;
	gSpriteClips[0].w = 22;
	gSpriteClips[0].h = 13;

	gSpriteClips[1].x = 29;
	gSpriteClips[1].y = 503;
	gSpriteClips[1].w = 29;
	gSpriteClips[1].h = 16;

	gSpriteClips[2].x = 61;
	gSpriteClips[2].y = 499;
	gSpriteClips[2].w = 25;
	gSpriteClips[2].h = 25;

	gSpriteClips[3].x = 96;
	gSpriteClips[3].y = 499;
	gSpriteClips[3].w = 35;
	gSpriteClips[3].h = 24;

	gSpriteClips[4].x = 141;
	gSpriteClips[4].y = 495;
	gSpriteClips[4].w = 42;
	gSpriteClips[4].h = 32;

	gSpriteClips[5].x = 186;
	gSpriteClips[5].y = 494;
	gSpriteClips[5].w = 46;
	gSpriteClips[5].h = 32;

	gSpriteClips[6].x = 235;
	gSpriteClips[6].y = 494;
	gSpriteClips[6].w = 47;
	gSpriteClips[6].h = 32;

	gSpriteClips[7].x = 285;
	gSpriteClips[7].y = 494;
	gSpriteClips[7].w = 47;
	gSpriteClips[7].h = 32;

	gSpriteClips[8].x = 335;
	gSpriteClips[8].y = 494;
	gSpriteClips[8].w = 39;
	gSpriteClips[8].h = 32;

	gSpriteClips[9].x = 377;
	gSpriteClips[9].y = 494;
	gSpriteClips[9].w = 37;
	gSpriteClips[9].h = 32;

	gSpriteClips[10].x = 417;
	gSpriteClips[10].y = 494;
	gSpriteClips[10].w = 35;
	gSpriteClips[10].h = 32;

	gSpriteClips[11].x = 455;
	gSpriteClips[11].y = 493;
	gSpriteClips[11].w = 32;
	gSpriteClips[11].h = 33;

	gSpriteClips[12].x = 493;
	gSpriteClips[12].y = 493;
	gSpriteClips[12].w = 33;
	gSpriteClips[12].h = 33;

	gSpriteClips[13].x = 531;
	gSpriteClips[13].y = 493;
	gSpriteClips[13].w = 31;
	gSpriteClips[13].h = 33;

	gSpriteClips[14].x = 567;
	gSpriteClips[14].y = 493;
	gSpriteClips[14].w = 25;
	gSpriteClips[14].h = 33;

	gSpriteClips[15].x = 1187;
	gSpriteClips[15].y = 505;
	gSpriteClips[15].w = 22;
	gSpriteClips[15].h = 13;

	gSpriteClips[16].x = 1154;
	gSpriteClips[16].y = 503;
	gSpriteClips[16].w = 29;
	gSpriteClips[16].h = 16;

	gSpriteClips[17].x = 1125;
	gSpriteClips[17].y = 499;
	gSpriteClips[17].w = 25;
	gSpriteClips[17].h = 25;

	gSpriteClips[18].x = 1079;
	gSpriteClips[18].y = 499;
	gSpriteClips[18].w = 35;
	gSpriteClips[18].h = 24;

	gSpriteClips[19].x = 1026;
	gSpriteClips[19].y = 495;
	gSpriteClips[19].w = 51;
	gSpriteClips[19].h = 15;

	gSpriteClips[20].x = 975;
	gSpriteClips[20].y = 494;
	gSpriteClips[20].w = 46;
	gSpriteClips[20].h = 32;

	gSpriteClips[21].x = 924;
	gSpriteClips[21].y = 494;
	gSpriteClips[21].w = 47;
	gSpriteClips[21].h = 32;

	gSpriteClips[22].x = 872;
	gSpriteClips[22].y = 494;
	gSpriteClips[22].w = 47;
	gSpriteClips[22].h = 32;

	gSpriteClips[23].x = 829;
	gSpriteClips[23].y = 494;
	gSpriteClips[23].w = 39;
	gSpriteClips[23].h = 32;

	gSpriteClips[24].x = 788;
	gSpriteClips[24].y = 494;
	gSpriteClips[24].w = 37;
	gSpriteClips[24].h = 32;

	gSpriteClips[25].x = 749;
	gSpriteClips[25].y = 494;
	gSpriteClips[25].w = 35;
	gSpriteClips[25].h = 32;

	gSpriteClips[26].x = 710;
	gSpriteClips[26].y = 493;
	gSpriteClips[26].w = 32;
	gSpriteClips[26].h = 33;

	gSpriteClips[27].x = 673;
	gSpriteClips[27].y = 493;
	gSpriteClips[27].w = 33;
	gSpriteClips[27].h = 33;

	gSpriteClips[28].x = 636;
	gSpriteClips[28].y = 493;
	gSpriteClips[28].w = 31;
	gSpriteClips[28].h = 33;

	gSpriteClips[29].x = 608;
	gSpriteClips[29].y = 493;
	gSpriteClips[29].w = 25;
	gSpriteClips[29].h = 33;

}
FlameShotImage::~FlameShotImage() {
	// TODO Auto-generated destructor stub
}

