/*
 * ZombieShot.cpp
 *
 *  Created on: 12/11/2016
 *      Author: usuario
 */

#include "ZombieShotImage.h"

ZombieShotImage::ZombieShotImage(SDL_Renderer* renderer,float scale):AnimationImage()  {
	this->scale = scale;
	this->texture = new LTexture(renderer,utils::FAT_ZOMBIE_DIR,scale);
	this->setSprites();
}
void ZombieShotImage::setSprites(){
	gSpriteClips[0].x = 13;
	gSpriteClips[0].y = 371;
	gSpriteClips[0].w = 23;
	gSpriteClips[0].h = 14;

	gSpriteClips[1].x = 47;
	gSpriteClips[1].y = 370;
	gSpriteClips[1].w = 26;
	gSpriteClips[1].h = 15;

	gSpriteClips[2].x = 79;
	gSpriteClips[2].y = 369;
	gSpriteClips[2].w = 25;
	gSpriteClips[2].h = 13;

	gSpriteClips[3].x = 112;
	gSpriteClips[3].y = 368;
	gSpriteClips[3].w = 23;
	gSpriteClips[3].h = 14;

	gSpriteClips[4].x = 145;
	gSpriteClips[4].y = 368;
	gSpriteClips[4].w = 23;
	gSpriteClips[4].h = 15;

	gSpriteClips[5].x = 177;
	gSpriteClips[5].y = 366;
	gSpriteClips[5].w = 23;
	gSpriteClips[5].h = 17;

	gSpriteClips[6].x = 212;
	gSpriteClips[6].y = 364;
	gSpriteClips[6].w = 22;
	gSpriteClips[6].h = 17;

	gSpriteClips[7].x = 244;
	gSpriteClips[7].y = 363;
	gSpriteClips[7].w = 22;
	gSpriteClips[7].h = 17;

	gSpriteClips[8].x = 278;
	gSpriteClips[8].y = 361;
	gSpriteClips[8].w = 23;
	gSpriteClips[8].h = 20;

	gSpriteClips[9].x = 309;
	gSpriteClips[9].y = 359;
	gSpriteClips[9].w = 22;
	gSpriteClips[9].h = 22;

	gSpriteClips[10].x = 341;
	gSpriteClips[10].y = 358;
	gSpriteClips[10].w = 20;
	gSpriteClips[10].h = 23;

	gSpriteClips[11].x = 373;
	gSpriteClips[11].y = 358;
	gSpriteClips[11].w = 20;
	gSpriteClips[11].h = 23;

	gSpriteClips[12].x = 406;
	gSpriteClips[12].y = 357;
	gSpriteClips[12].w = 19;
	gSpriteClips[12].h = 26;

//Dissapearing

	gSpriteClips[13].x = 6;
	gSpriteClips[13].y = 326;
	gSpriteClips[13].w = 8;
	gSpriteClips[13].h = 11;

	gSpriteClips[14].x = 24;
	gSpriteClips[14].y = 323;
	gSpriteClips[14].w = 16;
	gSpriteClips[14].h = 18;

	gSpriteClips[15].x = 50;
	gSpriteClips[15].y = 318;
	gSpriteClips[15].w = 28;
	gSpriteClips[15].h = 28;

	gSpriteClips[16].x = 88;
	gSpriteClips[16].y = 315;
	gSpriteClips[16].w = 32;
	gSpriteClips[16].h = 33;

	gSpriteClips[17].x = 130;
	gSpriteClips[17].y = 314;
	gSpriteClips[17].w = 35;
	gSpriteClips[17].h = 36;

	gSpriteClips[18].x = 175;
	gSpriteClips[18].y = 311;
	gSpriteClips[18].w = 38;
	gSpriteClips[18].h = 42;

	gSpriteClips[19].x = 223;
	gSpriteClips[19].y = 311;
	gSpriteClips[19].w = 39;
	gSpriteClips[19].h = 42;

	gSpriteClips[20].x = 272;
	gSpriteClips[20].y = 311;
	gSpriteClips[20].w = 41;
	gSpriteClips[20].h = 41;


//Left

	gSpriteClips[21].x = 1647;
	gSpriteClips[21].y = 357;
	gSpriteClips[21].w = 19;
	gSpriteClips[21].h = 26;

	gSpriteClips[22].x = 1611;
	gSpriteClips[22].y = 369;
	gSpriteClips[22].w = 25;
	gSpriteClips[22].h = 13;

	gSpriteClips[23].x = 1580;
	gSpriteClips[23].y = 368;
	gSpriteClips[23].w = 23;
	gSpriteClips[23].h = 14;

	gSpriteClips[24].x = 1547;
	gSpriteClips[24].y = 368;
	gSpriteClips[24].w = 23;
	gSpriteClips[24].h = 15;

	gSpriteClips[25].x = 1513;
	gSpriteClips[25].y = 366;
	gSpriteClips[25].w = 23;
	gSpriteClips[25].h = 17;

	gSpriteClips[26].x = 1481;
	gSpriteClips[26].y = 364;
	gSpriteClips[26].w = 22;
	gSpriteClips[26].h = 17;

	gSpriteClips[27].x = 1446;
	gSpriteClips[27].y = 363;
	gSpriteClips[27].w = 22;
	gSpriteClips[27].h = 17;

	gSpriteClips[28].x = 1414;
	gSpriteClips[28].y = 361;
	gSpriteClips[28].w = 23;
	gSpriteClips[28].h = 20;

	gSpriteClips[29].x = 1380;
	gSpriteClips[29].y = 359;
	gSpriteClips[29].w = 22;
	gSpriteClips[29].h = 22;

	gSpriteClips[30].x = 1350;
	gSpriteClips[30].y = 358;
	gSpriteClips[30].w = 20;
	gSpriteClips[30].h = 23;

	gSpriteClips[31].x = 1317;
	gSpriteClips[31].y = 358;
	gSpriteClips[31].w = 20;
	gSpriteClips[31].h = 23;

	gSpriteClips[32].x = 1287;
	gSpriteClips[32].y = 357;
	gSpriteClips[32].w = 19;
	gSpriteClips[32].h = 26;

	gSpriteClips[12].x = 1254;
	gSpriteClips[12].y = 357;
	gSpriteClips[12].w = 19;
	gSpriteClips[12].h = 26;


	//Dissapearing
	gSpriteClips[33].x = 1671;
	gSpriteClips[33].y = 326;
	gSpriteClips[33].w = 8;
	gSpriteClips[33].h = 11;


	gSpriteClips[34].x = 1645;
	gSpriteClips[34].y = 323;
	gSpriteClips[34].w = 16;
	gSpriteClips[34].h = 18;

	gSpriteClips[35].x = 1606;
	gSpriteClips[35].y = 318;
	gSpriteClips[35].w = 28;
	gSpriteClips[35].h = 28;

	gSpriteClips[36].x = 1564;
	gSpriteClips[36].y = 315;
	gSpriteClips[36].w = 32;
	gSpriteClips[36].h = 33;

	gSpriteClips[37].x = 1518;
	gSpriteClips[37].y = 314;
	gSpriteClips[37].w = 35;
	gSpriteClips[37].h = 36;

	gSpriteClips[38].x = 1469;
	gSpriteClips[38].y = 311;
	gSpriteClips[38].w = 38;
	gSpriteClips[38].h = 42;

	gSpriteClips[39].x = 1420;
	gSpriteClips[39].y = 311;
	gSpriteClips[39].w = 39;
	gSpriteClips[39].h = 42;

	gSpriteClips[40].x = 1368;
	gSpriteClips[40].y = 311;
	gSpriteClips[40].w = 41;
	gSpriteClips[40].h = 41;
}
ZombieShotImage::~ZombieShotImage() {
	// TODO Auto-generated destructor stub
}

