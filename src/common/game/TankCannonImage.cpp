/*
 * TankCannonImage.cpp
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#include "TankCannonImage.h"

TankCannonImage::TankCannonImage(SDL_Renderer* renderer,float scale):AnimationImage() {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::ENEMY_TANK,scale);
	this->setSprites();
}
void TankCannonImage::setSprites(){
	gSpriteClips[0].x = 399;
	gSpriteClips[0].y = 902;
	gSpriteClips[0].w = 46;
	gSpriteClips[0].h = 21;

	gSpriteClips[18].x = 350;
	gSpriteClips[18].y = 901;
	gSpriteClips[18].w = 46;
	gSpriteClips[18].h = 22;

	gSpriteClips[2].x = 301;
	gSpriteClips[2].y = 901;
	gSpriteClips[2].w = 46;
	gSpriteClips[2].h = 22;

	gSpriteClips[3].x = 252;
	gSpriteClips[3].y = 902;
	gSpriteClips[3].w = 46;
	gSpriteClips[3].h = 21;

	gSpriteClips[4].x = 133;
	gSpriteClips[4].y = 860;
	gSpriteClips[4].w = 47;
	gSpriteClips[4].h = 27;

	gSpriteClips[5].x = 183;
	gSpriteClips[5].y = 856;
	gSpriteClips[5].w = 49;
	gSpriteClips[5].h = 33;

	gSpriteClips[6].x = 235;
	gSpriteClips[6].y = 853;
	gSpriteClips[6].w = 50;
	gSpriteClips[6].h = 36;

	gSpriteClips[7].x = 288;
	gSpriteClips[7].y = 850;
	gSpriteClips[7].w = 52;
	gSpriteClips[7].h = 39;

	gSpriteClips[8].x = 342;
	gSpriteClips[8].y = 848;
	gSpriteClips[8].w = 51;
	gSpriteClips[8].h = 39;

	gSpriteClips[9].x = 396;
	gSpriteClips[9].y = 847;
	gSpriteClips[9].w = 48;
	gSpriteClips[9].h = 41;

	gSpriteClips[10].x = 447;
	gSpriteClips[10].y = 846;
	gSpriteClips[10].w = 40;
	gSpriteClips[10].h = 39;

	gSpriteClips[11].x = 3;
	gSpriteClips[11].y = 893;
	gSpriteClips[11].w = 44;
	gSpriteClips[11].h = 39;

	gSpriteClips[12].x = 53;
	gSpriteClips[12].y = 892;
	gSpriteClips[12].w = 39;
	gSpriteClips[12].h = 37;

	gSpriteClips[13].x = 98;
	gSpriteClips[13].y = 892;
	gSpriteClips[13].w = 38;
	gSpriteClips[13].h = 36;

	gSpriteClips[14].x = 139;
	gSpriteClips[14].y = 893;
	gSpriteClips[14].w = 38;
	gSpriteClips[14].h = 33;

	gSpriteClips[15].x = 180;
	gSpriteClips[15].y = 893;
	gSpriteClips[15].w = 32;
	gSpriteClips[15].h = 33;

	gSpriteClips[16].x = 219;
	gSpriteClips[16].y = 894;
	gSpriteClips[16].w = 24;
	gSpriteClips[16].h = 34;

	gSpriteClips[17].x = 625;
	gSpriteClips[17].y = 902;
	gSpriteClips[17].w = 46;
	gSpriteClips[17].h = 21;

	gSpriteClips[18].x = 674;
	gSpriteClips[18].y = 901;
	gSpriteClips[18].w = 46;
	gSpriteClips[18].h = 22;

	gSpriteClips[19].x = 723;
	gSpriteClips[19].y = 901;
	gSpriteClips[19].w = 46;
	gSpriteClips[19].h = 22;

	gSpriteClips[20].x = 772;
	gSpriteClips[20].y = 902;
	gSpriteClips[20].w = 46;
	gSpriteClips[20].h = 21;

	gSpriteClips[21].x = 890;
	gSpriteClips[21].y = 860;
	gSpriteClips[21].w = 47;
	gSpriteClips[21].h = 27;

	gSpriteClips[22].x = 838;
	gSpriteClips[22].y = 856;
	gSpriteClips[22].w = 49;
	gSpriteClips[22].h = 33;

	gSpriteClips[23].x = 785;
	gSpriteClips[23].y = 853;
	gSpriteClips[23].w = 50;
	gSpriteClips[23].h = 36;

	gSpriteClips[24].x = 730;
	gSpriteClips[24].y = 850;
	gSpriteClips[24].w = 52;
	gSpriteClips[24].h = 39;

	gSpriteClips[25].x = 677;
	gSpriteClips[25].y = 848;
	gSpriteClips[25].w = 51;
	gSpriteClips[25].h = 39;

	gSpriteClips[26].x = 626;
	gSpriteClips[26].y = 847;
	gSpriteClips[26].w = 48;
	gSpriteClips[26].h = 41;

	gSpriteClips[27].x = 583;
	gSpriteClips[27].y = 846;
	gSpriteClips[27].w = 40;
	gSpriteClips[27].h = 39;

	gSpriteClips[28].x = 1023;
	gSpriteClips[28].y = 893;
	gSpriteClips[28].w = 44;
	gSpriteClips[28].h = 39;

	gSpriteClips[29].x = 978;
	gSpriteClips[29].y = 892;
	gSpriteClips[29].w = 39;
	gSpriteClips[29].h = 37;

	gSpriteClips[30].x = 934;
	gSpriteClips[30].y = 892;
	gSpriteClips[30].w = 38;
	gSpriteClips[30].h = 36;

	gSpriteClips[31].x = 893;
	gSpriteClips[31].y = 893;
	gSpriteClips[31].w = 38;
	gSpriteClips[31].h = 33;

	gSpriteClips[32].x = 858;
	gSpriteClips[32].y = 893;
	gSpriteClips[32].w = 32;
	gSpriteClips[32].h = 33;

	gSpriteClips[33].x = 827;
	gSpriteClips[33].y = 894;
	gSpriteClips[33].w = 24;
	gSpriteClips[33].h = 34;
}
TankCannonImage::~TankCannonImage() {
	// TODO Auto-generated destructor stub
}

