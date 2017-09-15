/*
 * TankEnemyImage.cpp
 *
 *  Created on: 13/11/2016
 *      Author: pablo
 */

#include "TankEnemyImage.h"

#include <iostream>

	//Initializes variables
TankEnemyImage:: TankEnemyImage(SDL_Renderer* renderer,std::string path, float scale):BossImage(renderer,path,scale){
	this->setSprites();
}


	//Deallocates memory
TankEnemyImage:: ~TankEnemyImage(){

}




void TankEnemyImage::changeImageState(){
	//cout<<"changing to"<< connected<<endl;
	if(!connected)
		this->texture->setColor(100,100,100);
	else
		this->texture->setColor(255,255,255);
}
	//Renders texture at given point
void TankEnemyImage:: render(){
	if(isDead)
		return;
	if(renderedState != connected){
		renderedState = connected;
		this->changeImageState();
	}
	this->texture->render(currentClip,flip);
}

void TankEnemyImage:: setStatus(int frame,int connection){
	this->setMainFrame(frame);
	if(connection != lastState){
		lastState = connection;
		if(connected)
			connected = false;
		else
			connected = true;
	}
}
void TankEnemyImage::setMainFrame(int frame){
	if(frame >= (TENEMY_FRAMES-1)){
			frame -= (TENEMY_FRAMES-1);
			flip=SDL_FLIP_HORIZONTAL;
		}
		else{
			flip = SDL_FLIP_NONE;
		}
		//cout<<frame<<endl;
		this->currentClip = gSpriteClips+frame;
}
void TankEnemyImage::setExtraFrame(int extraFrame){

}
/*
void TankEnemyImage::setFrameProperties(int frame){
	if(frame >= TENEMY_FRAMES){
		frame -= TENEMY_FRAMES;
		flip=SDL_FLIP_HORIZONTAL;
	}
	else{
		flip = SDL_FLIP_NONE;
	}
	this->currentClip = gSpriteClips+frame;
}*/
void TankEnemyImage::setSprites(){

	//IDLE
	gSpriteClips[0].x = 3;
	gSpriteClips[0].y = 3;
	gSpriteClips[0].w = 71;
	gSpriteClips[0].h = 56;

	gSpriteClips[1].x = 77;
	gSpriteClips[1].y = 3;
	gSpriteClips[1].w = 71;
	gSpriteClips[1].h = 56;

	//Driving 
	gSpriteClips[2].x = 3;
	gSpriteClips[2].y = 62;
	gSpriteClips[2].w = 71;
	gSpriteClips[2].h = 56;

	gSpriteClips[3].x = 77;
	gSpriteClips[3].y = 62;
	gSpriteClips[3].w = 72;
	gSpriteClips[3].h = 56;

	gSpriteClips[4].x = 152;
	gSpriteClips[4].y = 62;
	gSpriteClips[4].w = 71;
	gSpriteClips[4].h = 56;

	gSpriteClips[5].x = 226;
	gSpriteClips[5].y = 61;
	gSpriteClips[5].w = 72;
	gSpriteClips[5].h = 56;

	gSpriteClips[6].x = 301;
	gSpriteClips[6].y = 62;
	gSpriteClips[6].w = 71;
	gSpriteClips[6].h = 56;

	gSpriteClips[7].x = 375;
	gSpriteClips[7].y = 61;
	gSpriteClips[7].w = 72;
	gSpriteClips[7].h = 57;

	//turning
	gSpriteClips[8].x = 3;
	gSpriteClips[8].y = 239;
	gSpriteClips[8].w = 69;
	gSpriteClips[8].h = 56;

	gSpriteClips[9].x = 75;
	gSpriteClips[9].y = 239;
	gSpriteClips[9].w = 69;
	gSpriteClips[9].h = 56;

	gSpriteClips[10].x = 147;
	gSpriteClips[10].y = 239;
	gSpriteClips[10].w = 68;
	gSpriteClips[10].h = 56;

	gSpriteClips[11].x = 218;
	gSpriteClips[11].y = 239;
	gSpriteClips[11].w = 68;
	gSpriteClips[11].h = 56;

	gSpriteClips[12].x = 289;
	gSpriteClips[12].y = 239;
	gSpriteClips[12].w = 66;
	gSpriteClips[12].h = 56;

	gSpriteClips[13].x = 358;
	gSpriteClips[13].y = 239;
	gSpriteClips[13].w = 59;
	gSpriteClips[13].h = 56;

	gSpriteClips[14].x = 420;
	gSpriteClips[14].y = 239;
	gSpriteClips[14].w = 66;
	gSpriteClips[14].h = 56;

	gSpriteClips[15].x = 3;
	gSpriteClips[15].y = 298;
	gSpriteClips[15].w = 68;
	gSpriteClips[15].h = 56;

	gSpriteClips[16].x = 74;
	gSpriteClips[16].y = 298;
	gSpriteClips[16].w = 68;
	gSpriteClips[16].h = 56;

	gSpriteClips[17].x = 145;
	gSpriteClips[17].y = 298;
	gSpriteClips[17].w = 69;
	gSpriteClips[17].h = 56;

	gSpriteClips[18].x = 217;
	gSpriteClips[18].y = 298;
	gSpriteClips[18].w = 69;
	gSpriteClips[18].h = 56;

	//Shooting
	gSpriteClips[19].x = 3;
	gSpriteClips[19].y = 359;
	gSpriteClips[19].w = 71;
	gSpriteClips[19].h = 59;

	gSpriteClips[20].x = 77;
	gSpriteClips[20].y = 359;
	gSpriteClips[20].w = 71;
	gSpriteClips[20].h = 59;

	gSpriteClips[21].x = 151;
	gSpriteClips[21].y = 359;
	gSpriteClips[21].w = 71;
	gSpriteClips[21].h = 59;

	gSpriteClips[22].x = 225;
	gSpriteClips[22].y = 357;
	gSpriteClips[22].w = 71;
	gSpriteClips[22].h = 61;

	gSpriteClips[23].x = 299;
	gSpriteClips[23].y = 360;
	gSpriteClips[23].w = 71;
	gSpriteClips[23].h = 58;

	gSpriteClips[24].x = 373;
	gSpriteClips[24].y = 362;
	gSpriteClips[24].w = 71;
	gSpriteClips[24].h = 56;

	gSpriteClips[25].x = 447;
	gSpriteClips[25].y = 362;
	gSpriteClips[25].w = 71;
	gSpriteClips[25].h = 56;


	gSpriteClips[26].x = 3;
	gSpriteClips[26].y = 425;
	gSpriteClips[26].w = 71;
	gSpriteClips[26].h = 56;


	gSpriteClips[27].x = 77;
	gSpriteClips[27].y = 424;
	gSpriteClips[27].w = 71;
	gSpriteClips[27].h = 57;

	gSpriteClips[28].x = 151;
	gSpriteClips[28].y = 423;
	gSpriteClips[28].w = 71;
	gSpriteClips[28].h = 58;

	gSpriteClips[29].x = 225;
	gSpriteClips[29].y = 421;
	gSpriteClips[29].w = 70;
	gSpriteClips[29].h = 60;

	//Dying
	gSpriteClips[30].x = 3;
	gSpriteClips[30].y = 490;
	gSpriteClips[30].w = 72;
	gSpriteClips[30].h = 53;

	gSpriteClips[31].x = 78;
	gSpriteClips[31].y = 494;
	gSpriteClips[31].w = 72;
	gSpriteClips[31].h = 49;

	gSpriteClips[32].x = 153;
	gSpriteClips[32].y = 484;
	gSpriteClips[32].w = 70;
	gSpriteClips[32].h = 59;

	gSpriteClips[33].x = 226;
	gSpriteClips[33].y = 488;
	gSpriteClips[33].w = 72;
	gSpriteClips[33].h = 55;

	gSpriteClips[34].x = 301;
	gSpriteClips[34].y = 489;
	gSpriteClips[34].w = 73;
	gSpriteClips[34].h = 54;

	gSpriteClips[35].x = 377;
	gSpriteClips[35].y = 489;
	gSpriteClips[35].w = 72;
	gSpriteClips[35].h = 54;

	gSpriteClips[36].x = 452;
	gSpriteClips[36].y = 491;
	gSpriteClips[36].w = 72;
	gSpriteClips[36].h = 52;

	gSpriteClips[37].x = 3;
	gSpriteClips[37].y = 557;
	gSpriteClips[37].w = 74;
	gSpriteClips[37].h = 53;

	gSpriteClips[38].x = 80;
	gSpriteClips[38].y = 546;
	gSpriteClips[38].w = 69;
	gSpriteClips[38].h = 64;

	gSpriteClips[39].x = 152;
	gSpriteClips[39].y = 553;
	gSpriteClips[39].w = 72;
	gSpriteClips[39].h = 57;

	gSpriteClips[40].x = 227;
	gSpriteClips[40].y = 558;
	gSpriteClips[40].w = 78;
	gSpriteClips[40].h = 52;

	gSpriteClips[41].x = 308;
	gSpriteClips[41].y = 559;
	gSpriteClips[41].w = 90;
	gSpriteClips[41].h = 51;

	gSpriteClips[42].x = 401;
	gSpriteClips[42].y = 559;
	gSpriteClips[42].w = 96;
	gSpriteClips[42].h = 51;

	gSpriteClips[43].x = 3;
	gSpriteClips[43].y = 618;
	gSpriteClips[43].w = 96;
	gSpriteClips[43].h = 63;

	gSpriteClips[44].x = 102;
	gSpriteClips[44].y = 614;
	gSpriteClips[44].w = 96;
	gSpriteClips[44].h = 67;

	gSpriteClips[45].x = 201;
	gSpriteClips[45].y = 613;
	gSpriteClips[45].w = 96;
	gSpriteClips[45].h = 68;

	gSpriteClips[46].x = 300;
	gSpriteClips[46].y = 619;
	gSpriteClips[46].w = 96;
	gSpriteClips[46].h = 62;

	gSpriteClips[47].x = 399;
	gSpriteClips[47].y = 623;
	gSpriteClips[47].w = 96;
	gSpriteClips[47].h = 58;

	gSpriteClips[48].x = 3;
	gSpriteClips[48].y = 683;
	gSpriteClips[48].w = 96;
	gSpriteClips[48].h = 66;

	gSpriteClips[49].x = 102;
	gSpriteClips[49].y = 684;
	gSpriteClips[49].w = 96;
	gSpriteClips[49].h = 55;

	gSpriteClips[50].x = 201;
	gSpriteClips[50].y = 684;
	gSpriteClips[50].w = 96;
	gSpriteClips[50].h = 55;

	gSpriteClips[51].x = 300;
	gSpriteClips[51].y = 683;
	gSpriteClips[51].w = 94;
	gSpriteClips[51].h = 56;

	gSpriteClips[52].x = 397;
	gSpriteClips[52].y = 686;
	gSpriteClips[52].w = 96;
	gSpriteClips[52].h = 53;

	gSpriteClips[53].x = 3;
	gSpriteClips[53].y = 740;
	gSpriteClips[53].w = 96;
	gSpriteClips[53].h = 49;

	gSpriteClips[54].x = 102;
	gSpriteClips[54].y = 743;
	gSpriteClips[54].w = 96;
	gSpriteClips[54].h = 46;


}
