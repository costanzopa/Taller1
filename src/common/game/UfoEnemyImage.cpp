/*
 * UfoEnemyImage.cpp
 *
 *  Created on: 5/11/2016
 *      Author: usuario
 */

#include "UfoEnemyImage.h"
#define SPRITE_SIN_RAYO 9
#include <iostream>

	//Initializes variables
using namespace std;
UfoEnemyImage:: UfoEnemyImage(SDL_Renderer* renderer,std::string path, float scale):BossImage(renderer,path,scale){
	this->setSprites();
	this->setLightSprites();
	lights = new LTexture(renderer,path,scale);
	flip=SDL_FLIP_NONE;
}


	//Deallocates memory
UfoEnemyImage:: ~UfoEnemyImage(){

}
void UfoEnemyImage::setMainFrame(int ufoFrame){
	this->currentClip = gSpriteClips +ufoFrame;
}
void UfoEnemyImage::setExtraFrame(int rayFrame){
	this->currentLightsClip = gLightClips + rayFrame;
}
void UfoEnemyImage::changeImageState(){
	cout<<"changing to"<< connected<<endl;
	if(!connected) {
		this->texture->setColor(100,100,100);
		this->lights->setColor(100,100,100);
	} else {
		this->texture->setColor(255,255,255);
		this->lights->setColor(255,255,255);
	}
}
	//Renders texture at given point
void UfoEnemyImage:: render(){
	if(isDead)
		return;
	if(renderedState != connected){
		renderedState = connected;
		this->changeImageState();
	}
	this->lights->render(currentLightsClip,flip);
	this->texture->render(currentClip,flip);
}

void UfoEnemyImage:: setStatus(int frame,int connection){
	this->setMainFrame(frame);
	if(connection != lastState){
		lastState = connection;
		if(connected)
			connected = false;
		else
			connected = true;
	}
}
/*
void UfoEnemyImage::setFrameProperties(int frame){
	if(frame<UFOENEMY_FRAMES){
		this->currentClip = gSpriteClips+frame;
		this->currentLightsClip = gLightClips+SPRITE_SIN_RAYO;
		return;
	}
	int finFrame = frame-UFOENEMY_FRAMES;
	this->currentClip = gSpriteClips+finFrame;
	this->currentLightsClip = gLightClips +finFrame;
}
*/
int UfoEnemyImage::getLightFrame(int frame) {
	int lf = 0;

	if(frame == 0 || frame == 11)
		lf = 5;

	if(frame == 1 || frame == 10)
		lf = 4;

	if(frame == 2 || frame == 9)
		lf = 3;

	if(frame == 3 || frame == 8)
		lf = 2;

	if(frame == 4 || frame == 7)
		lf = 1;

	return lf;
}

void UfoEnemyImage::setPosition(int x,int y){
	int y_light = y + this->currentClip->h;
	int x_light = x;

	if(this->currentClip->w > this->currentLightsClip->w) {
		x_light = x + ((this->currentClip->w - this->currentLightsClip->w) / 2);
	}

	this->texture->setPosition(x,y);
	this->lights->setPosition(x_light,y_light);
}

void UfoEnemyImage::setSprites(){

	//Walking
	gSpriteClips[0].x = 2;
	gSpriteClips[0].y = 2;
	gSpriteClips[0].w = 53;
	gSpriteClips[0].h = 30;

	gSpriteClips[1].x = 60;
	gSpriteClips[1].y = 2;
	gSpriteClips[1].w = 53;
	gSpriteClips[1].h = 30;

	gSpriteClips[2].x = 118;
	gSpriteClips[2].y = 2;
	gSpriteClips[2].w = 53;
	gSpriteClips[2].h = 30;

	gSpriteClips[3].x = 176;
	gSpriteClips[3].y = 2;
	gSpriteClips[3].w = 53;
	gSpriteClips[3].h = 30;

	gSpriteClips[4].x = 234;
	gSpriteClips[4].y = 2;
	gSpriteClips[4].w = 53;
	gSpriteClips[4].h = 31;

	gSpriteClips[5].x = 293;
	gSpriteClips[5].y = 2;
	gSpriteClips[5].w = 53;
	gSpriteClips[5].h = 31;

	gSpriteClips[6].x = 351;
	gSpriteClips[6].y = 2;
	gSpriteClips[6].w = 53;
	gSpriteClips[6].h = 31;

	gSpriteClips[7].x = 409;
	gSpriteClips[7].y = 2;
	gSpriteClips[7].w = 53;
	gSpriteClips[7].h = 31;

	gSpriteClips[8].x = 467;
	gSpriteClips[8].y = 2;
	gSpriteClips[8].w = 53;
	gSpriteClips[8].h = 31;

	gSpriteClips[9].x = 525;
	gSpriteClips[9].y = 2;
	gSpriteClips[9].w = 53;
	gSpriteClips[9].h = 31;

	gSpriteClips[10].x = 583;
	gSpriteClips[10].y = 2;
	gSpriteClips[10].w = 53;
	gSpriteClips[10].h = 30;

	gSpriteClips[11].x = 641;
	gSpriteClips[11].y = 2;
	gSpriteClips[11].w = 53;
	gSpriteClips[11].h = 30;

}

void UfoEnemyImage::setLightSprites(){

	gLightClips[0].x = 177;
	gLightClips[0].y = 48;
	gLightClips[0].w = 14;
	gLightClips[0].h = 7;

	gLightClips[1].x = 204;
	gLightClips[1].y = 48;
	gLightClips[1].w = 16;
	gLightClips[1].h = 10;

	gLightClips[2].x = 229;
	gLightClips[2].y = 48;
	gLightClips[2].w = 24;
	gLightClips[2].h = 23;

	gLightClips[3].x = 262;
	gLightClips[3].y = 48;
	gLightClips[3].w = 20;
	gLightClips[3].h = 31;

	gLightClips[4].x = 290;
	gLightClips[4].y = 48;
	gLightClips[4].w = 28;
	gLightClips[4].h = 39;

	gLightClips[5].x = 324;
	gLightClips[5].y = 48;
	gLightClips[5].w = 38;
	gLightClips[5].h = 71;

	gLightClips[6].x = 369;
	gLightClips[6].y = 48;
	gLightClips[6].w = 44;
	gLightClips[6].h = 38;

	gLightClips[7].x = 428;
	gLightClips[7].y = 48;
	gLightClips[7].w = 8;
	gLightClips[7].h = 35;

	gLightClips[8].x = 458;
	gLightClips[8].y = 48;
	gLightClips[8].w = 8;
	gLightClips[8].h = 14;


//Sin rayo

	gLightClips[9].x = 478;
	gLightClips[9].y = 48;
	gLightClips[9].w = 8;
	gLightClips[9].h = 14;




}
