/*
 * MeleeEnemyImage.cpp
 *
 *  Created on: 5/11/2016
 *      Author: usuario
 */

#include "MeleeEnemyImage.h"

#include <iostream>

	//Initializes variables
MeleeEnemyImage:: MeleeEnemyImage(SDL_Renderer* renderer,std::string path, float scale):EnemyImage(renderer,path,scale){
	this->setSprites();
}


	//Deallocates memory
MeleeEnemyImage:: ~MeleeEnemyImage(){

}




void MeleeEnemyImage::changeImageState(){
	cout<<"changing to"<< connected<<endl;
	if(!connected)
		this->texture->setColor(100,100,100);
	else
		this->texture->setColor(255,255,255);
}
	//Renders texture at given point
void MeleeEnemyImage:: render(){
	if(isDead)
		return;
	if(renderedState != connected){
		renderedState = connected;
		this->changeImageState();
	}
	this->texture->render(currentClip,flip);
}

void MeleeEnemyImage:: setStatus(int frame,int connection){
	this->setFrameProperties(frame);
	if(connection != lastState){
		lastState = connection;
		if(connected)
			connected = false;
		else
			connected = true;
	}
}
void MeleeEnemyImage::setPosition(int x,int y){
	int real_y = y + 41 - this->currentClip->h;
	this->texture->setPosition(x,real_y);
}
void MeleeEnemyImage::setFrameProperties(int frame){
	if(frame >= MENEMY_FRAMES){
		frame -= MENEMY_FRAMES;
		flip=SDL_FLIP_HORIZONTAL;
	}
	else{
		flip = SDL_FLIP_NONE;
	}
	this->currentClip = gSpriteClips+frame;
}
void MeleeEnemyImage::setSprites(){

	//Walking
	gSpriteClips[0].x = 6;
	gSpriteClips[0].y = 124;
	gSpriteClips[0].w = 35;
	gSpriteClips[0].h = 37;

	gSpriteClips[1].x = 46;
	gSpriteClips[1].y = 124;
	gSpriteClips[1].w = 33;
	gSpriteClips[1].h = 37;

	gSpriteClips[2].x = 84;
	gSpriteClips[2].y = 124;
	gSpriteClips[2].w = 34;
	gSpriteClips[2].h = 37;

	gSpriteClips[3].x = 123;
	gSpriteClips[3].y = 123;
	gSpriteClips[3].w = 35;
	gSpriteClips[3].h = 38;

	gSpriteClips[4].x = 163;
	gSpriteClips[4].y = 122;
	gSpriteClips[4].w = 36;
	gSpriteClips[4].h = 39;

	gSpriteClips[5].x = 204;
	gSpriteClips[5].y = 123;
	gSpriteClips[5].w = 36;
	gSpriteClips[5].h = 38;

	gSpriteClips[6].x = 245;
	gSpriteClips[6].y = 124;
	gSpriteClips[6].w = 36;
	gSpriteClips[6].h = 47;

	gSpriteClips[7].x = 286;
	gSpriteClips[7].y = 124;
	gSpriteClips[7].w = 36;
	gSpriteClips[7].h = 37;

	gSpriteClips[8].x = 327;
	gSpriteClips[8].y = 124;
	gSpriteClips[8].w = 36;
	gSpriteClips[8].h = 37;

	gSpriteClips[9].x = 368;
	gSpriteClips[9].y = 124;
	gSpriteClips[9].w = 36;
	gSpriteClips[9].h = 37;

	gSpriteClips[10].x = 409;
	gSpriteClips[10].y = 123;
	gSpriteClips[10].w = 35;
	gSpriteClips[10].h = 38;

	gSpriteClips[11].x = 449;
	gSpriteClips[11].y = 122;
	gSpriteClips[11].w = 34;
	gSpriteClips[11].h = 39;

	gSpriteClips[12].x = 488;
	gSpriteClips[12].y = 123;
	gSpriteClips[12].w = 33;
	gSpriteClips[12].h = 38;


	gSpriteClips[13].x = 526;
	gSpriteClips[13].y = 124;
	gSpriteClips[13].w = 33;
	gSpriteClips[13].h = 33;

	//Attacking
	gSpriteClips[14].x = 6;
	gSpriteClips[14].y = 267;
	gSpriteClips[14].w = 39;
	gSpriteClips[14].h = 39;

	gSpriteClips[15].x = 50;
	gSpriteClips[15].y = 267;
	gSpriteClips[15].w = 39;
	gSpriteClips[15].h = 39;

	gSpriteClips[16].x = 94;
	gSpriteClips[16].y = 267;
	gSpriteClips[16].w = 40;
	gSpriteClips[16].h = 39;

	gSpriteClips[17].x = 139;
	gSpriteClips[17].y = 267;
	gSpriteClips[17].w = 37;
	gSpriteClips[17].h = 39;

	gSpriteClips[18].x = 181;
	gSpriteClips[18].y = 267;
	gSpriteClips[18].w = 37;
	gSpriteClips[18].h = 39;

	gSpriteClips[19].x = 223;
	gSpriteClips[19].y = 267;
	gSpriteClips[19].w = 36;
	gSpriteClips[19].h = 39;

	gSpriteClips[20].x = 264;
	gSpriteClips[20].y = 267;
	gSpriteClips[20].w = 37;
	gSpriteClips[20].h = 39;


	gSpriteClips[21].x = 306;
	gSpriteClips[21].y = 267;
	gSpriteClips[21].w = 39;
	gSpriteClips[21].h = 39;

	gSpriteClips[22].x = 350;
	gSpriteClips[22].y = 267;
	gSpriteClips[22].w = 35;
	gSpriteClips[22].h = 39;

	gSpriteClips[23].x = 390;
	gSpriteClips[23].y = 267;
	gSpriteClips[23].w = 34;
	gSpriteClips[23].h = 39;

	gSpriteClips[24].x = 429;
	gSpriteClips[24].y = 267;
	gSpriteClips[24].w = 36;
	gSpriteClips[24].h = 39;

	gSpriteClips[25].x = 470;
	gSpriteClips[25].y = 267;
	gSpriteClips[25].w = 37;
	gSpriteClips[25].h = 39;


	gSpriteClips[26].x = 512;
	gSpriteClips[26].y = 267;
	gSpriteClips[26].w = 37;
	gSpriteClips[26].h = 39;


	gSpriteClips[27].x = 554;
	gSpriteClips[27].y = 267;
	gSpriteClips[27].w = 37;
	gSpriteClips[27].h = 39;

	gSpriteClips[28].x = 596;
	gSpriteClips[28].y = 267;
	gSpriteClips[28].w = 37;
	gSpriteClips[28].h = 39;

	gSpriteClips[29].x = 638;
	gSpriteClips[29].y = 267;
	gSpriteClips[29].w = 36;
	gSpriteClips[29].h = 39;

	gSpriteClips[30].x = 679;
	gSpriteClips[30].y = 267;
	gSpriteClips[30].w = 34;
	gSpriteClips[30].h = 39;

	gSpriteClips[31].x = 718;
	gSpriteClips[31].y = 267;
	gSpriteClips[31].w = 35;
	gSpriteClips[31].h = 39;


	//DYING
	gSpriteClips[32].x = 511;
	gSpriteClips[32].y = 76;
	gSpriteClips[32].w = 39;
	gSpriteClips[32].h = 37;

	gSpriteClips[33].x = 467;
	gSpriteClips[33].y = 76;
	gSpriteClips[33].w = 39;
	gSpriteClips[33].h = 37;

	gSpriteClips[34].x = 423;
	gSpriteClips[34].y = 76;
	gSpriteClips[34].w = 39;
	gSpriteClips[34].h = 37;


	gSpriteClips[35].x = 378;
	gSpriteClips[35].y = 76;
	gSpriteClips[35].w = 40;
	gSpriteClips[35].h = 37;

	gSpriteClips[36].x = 336;
	gSpriteClips[36].y = 76;
	gSpriteClips[36].w = 32;
	gSpriteClips[36].h = 37;

	gSpriteClips[37].x = 297;
	gSpriteClips[37].y = 76;
	gSpriteClips[37].w = 32;
	gSpriteClips[37].h = 37;

	gSpriteClips[38].x = 257;
	gSpriteClips[38].y = 76;
	gSpriteClips[38].w = 35;
	gSpriteClips[38].h = 37;

	gSpriteClips[39].x = 216;
	gSpriteClips[39].y = 76;
	gSpriteClips[39].w = 36;
	gSpriteClips[39].h = 37;


	gSpriteClips[40].x = 174;
	gSpriteClips[40].y = 76;
	gSpriteClips[40].w = 37;
	gSpriteClips[40].h = 37;


	gSpriteClips[41].x = 131;
	gSpriteClips[41].y = 76;
	gSpriteClips[41].w = 38;
	gSpriteClips[41].h = 37;

	gSpriteClips[42].x = 88;
	gSpriteClips[42].y = 76;
	gSpriteClips[42].w = 38;
	gSpriteClips[42].h = 37;

	gSpriteClips[43].x = 47;
	gSpriteClips[43].y = 76;
	gSpriteClips[43].w = 36;
	gSpriteClips[43].h = 37;

	gSpriteClips[44].x = 6;
	gSpriteClips[44].y = 76;
	gSpriteClips[44].w = 36;
	gSpriteClips[44].h = 37;


}
