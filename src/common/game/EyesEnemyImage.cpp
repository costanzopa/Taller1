/*
 * EyesEnemyImage.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: rodri
 */

#include "EyesEnemyImage.h"

namespace std {

EyesEnemyImage::EyesEnemyImage(SDL_Renderer* renderer,std::string path, float scale):BossImage(renderer,path,scale) {
	this->setSprites();
	this->setLaserSprites();
	laser = new LTexture(renderer,path,scale);
}
void EyesEnemyImage::changeImageState(){
	if(!connected) {
		this->texture->setColor(100,100,100);
		this->laser->setColor(100,100,100);
	} else {
		this->texture->setColor(255,255,255);
		this->laser->setColor(255,255,255);
	}
}

void EyesEnemyImage:: render(){
	if(isDead)
		return;
	if(renderedState != connected){
		renderedState = connected;
		this->changeImageState();
	}
	this->texture->render(currentClip,flip);
	this->laser->render(currentLaserClip,flip);
}
void EyesEnemyImage:: setStatus(int frame,int connection){
	this->setMainFrame(frame);
	if(connection != lastState){
		lastState = connection;
		if(connected)
			connected = false;
		else
			connected = true;
	}
}
void EyesEnemyImage::setExtraFrame(int frame){
	this->currentLaserClip = gLaserClips+frame;
}
void EyesEnemyImage::setMainFrame(int frame){
	this->currentClip = gSpriteClips + frame;
}

void EyesEnemyImage::setPosition(int x,int y){
	int y_light = y + this->currentClip->h/2;
	int x_light = x;

	this->texture->setPosition(x,y);
	this->laser->setPosition(x_light,y_light);
}


void EyesEnemyImage::setSprites(){

	//IDLE

	gSpriteClips[0].x = 5;
	gSpriteClips[0].y = 37;
	gSpriteClips[0].w = 35;
	gSpriteClips[0].h = 32;

	gSpriteClips[1].x = 43;
	gSpriteClips[1].y = 37;
	gSpriteClips[1].w = 35;
	gSpriteClips[1].h = 32;

	gSpriteClips[2].x = 81;
	gSpriteClips[2].y = 37;
	gSpriteClips[2].w = 35;
	gSpriteClips[2].h = 32;

	gSpriteClips[3].x = 119;
	gSpriteClips[3].y = 37;
	gSpriteClips[3].w = 35;
	gSpriteClips[3].h = 32;

	gSpriteClips[4].x = 157;
	gSpriteClips[4].y = 37;
	gSpriteClips[4].w = 35;
	gSpriteClips[4].h = 32;

	gSpriteClips[5].x = 195;
	gSpriteClips[5].y = 37;
	gSpriteClips[5].w = 35;
	gSpriteClips[5].h = 32;

	gSpriteClips[6].x = 269;
	gSpriteClips[6].y = 37;
	gSpriteClips[6].w = 35;
	gSpriteClips[6].h = 32;


	gSpriteClips[7].x = 343;
	gSpriteClips[7].y = 37;
	gSpriteClips[7].w = 35;
	gSpriteClips[7].h = 32;

	gSpriteClips[8].x = 380;
	gSpriteClips[8].y = 37;
	gSpriteClips[8].w = 35;
	gSpriteClips[8].h = 32;

	gSpriteClips[9].x = 426;
	gSpriteClips[9].y = 37;
	gSpriteClips[9].w = 35;
	gSpriteClips[9].h = 32;

	gSpriteClips[10].x = 464;
	gSpriteClips[10].y = 37;
	gSpriteClips[10].w = 35;
	gSpriteClips[10].h = 32;


	gSpriteClips[11].x = 540;
	gSpriteClips[11].y = 37;
	gSpriteClips[11].w = 35;
	gSpriteClips[11].h = 32;


	gSpriteClips[12].x = 616;
	gSpriteClips[12].y = 37;
	gSpriteClips[12].w = 35;
	gSpriteClips[12].h = 32;

	gSpriteClips[13].x = 655;
	gSpriteClips[13].y = 37;
	gSpriteClips[13].w = 35;
	gSpriteClips[13].h = 32;

	gSpriteClips[14].x = 694;
	gSpriteClips[14].y = 37;
	gSpriteClips[14].w = 35;
	gSpriteClips[14].h = 32;

	gSpriteClips[15].x = 734;
	gSpriteClips[15].y = 37;
	gSpriteClips[15].w = 35;
	gSpriteClips[15].h = 32;

	gSpriteClips[16].x = 773;
	gSpriteClips[16].y = 37;
	gSpriteClips[16].w = 36;
	gSpriteClips[16].h = 32;

	gSpriteClips[17].x = 813;
	gSpriteClips[17].y = 37;
	gSpriteClips[17].w = 35;
	gSpriteClips[17].h = 32;
}


void EyesEnemyImage::setLaserSprites(){

	gLaserClips[0].x = 7;
	gLaserClips[0].y = 147;
	gLaserClips[0].w = 19;
	gLaserClips[0].h = 23;

	gLaserClips[1].x = 30;
	gLaserClips[1].y = 143;
	gLaserClips[1].w = 23;
	gLaserClips[1].h = 30;

	gLaserClips[2].x = 56;
	gLaserClips[2].y = 140;
	gLaserClips[2].w = 26;
	gLaserClips[2].h = 34;

	gLaserClips[3].x = 85;
	gLaserClips[3].y = 146;
	gLaserClips[3].w = 20;
	gLaserClips[3].h = 24;

	gLaserClips[4].x = 108;
	gLaserClips[4].y = 150;
	gLaserClips[4].w = 16;
	gLaserClips[4].h = 16;

	gLaserClips[5].x = 127;
	gLaserClips[5].y = 152;
	gLaserClips[5].w = 16;
	gLaserClips[5].h = 12;

	gLaserClips[6].x = 146;
	gLaserClips[6].y = 153;
	gLaserClips[6].w = 13;
	gLaserClips[6].h = 10;

	gLaserClips[7].x = 162;
	gLaserClips[7].y = 155;
	gLaserClips[7].w = 11;
	gLaserClips[7].h = 7;

	gLaserClips[8].x = 162;
	gLaserClips[8].y = 170;
	gLaserClips[8].w = 11;
	gLaserClips[8].h = 7;


}

EyesEnemyImage::~EyesEnemyImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
