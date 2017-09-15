/*
void GameImage::setPosition(int x,int y){
	this->texture->setPosition(x,y);
}
 * CharacterImage.cpp
 *
 *  Created on: 25/09/2016
 *      Author: guido
 */
#include "CharacterImage.h"
#include <iostream>


	//Initializes variables
CharacterImage:: CharacterImage(SDL_Renderer* renderer,std::string path, float scale){
	//texture = new LTexture(renderer,path);
	this->scale = scale;
	texture = new LTexture(renderer,path,scale);
	legs = new LTexture(renderer,path,scale);
	isDead = false;
	connected = true;
	renderedState = true;
	lastState = 1;
	this->offset = 0;
	this->setSprites();
	this->setLegSprites();
}


	//Deallocates memory
CharacterImage:: ~CharacterImage(){
	delete texture;
	delete legs;
}

void CharacterImage:: setStatus(int frame,int connection){
	if(isDead)
		return;
	this->setFrameProperties(frame);
	if(connection != lastState){
		lastState = connection;
		if(connected)
			connected = false;
		else
			connected = true;
	}
}


void CharacterImage::changeImageState(){
	//cout<<"changing to"<< connected<<endl;
	if(!connected)
		this->texture->setColor(100,100,100);
	else
		this->texture->setColor(255,255,255);
}
void CharacterImage::changeLegsState(){
	if(!connected)
		this->legs->setColor(100,100,100);
	else
		this->legs->setColor(255,255,255);
}


	//Renders texture at given point
void CharacterImage:: render(){
	if(this->isDead)
		return;
	if(renderedState != connected){
		renderedState = connected;
		this->changeLegsState();
		this->changeImageState();
	}
	this->legs->render(currentLegClip,SDL_FLIP_NONE);
	this->texture->render(currentClip,SDL_FLIP_NONE);
}

void CharacterImage:: setLegStatus(int legNumber){
	this->setLegFrameProperties(legNumber);
}

void CharacterImage::setLegFrameProperties(int frame){
	this->currentLegClip = gLegClips+frame;
}
void CharacterImage::setFrameProperties(int frame){
	if(frame >= ANIMATION_FRAMES/2)
		goingLeft = true;
	else
		goingLeft =false;

	//cout << "Character frame: " << frame << endl;
	this->setOffset(frame);
	this->currentClip = gSpriteClips+frame;
}

void CharacterImage::setOffset(int i){
	if(i >= ANIMATION_FRAMES/2)
		i -= ANIMATION_FRAMES/2;
	if(i < 76){
		if(i<4){
			this->offset = 8;
				return;
		}
		if(i>=4){
			this->offset = 3;
		}
		if(26<=i && i<=36){
			this->offset = 10;
			return;
		}
		if(i==29){
			this->offset = 3;
			return;
		}
		if(64<=i && i<=75){
			this->offset = 15;
		}
		if(68<=i && i<=71){
			this->offset = 5;
		}
	}
	else{
		i -= 76;
		if(i<4){
			this->offset = 6;
			return;
		}
		if(4<=i<=10){
			this->offset = 8;
		}
		if(i>10){
			this->offset = 3;
		}
		if(26<=i && i<=36){
			this->offset = 10;
			return;
		}
		if(i==29){
			this->offset = 3;
			return;
		}
		if(64<=i && i<=75){
			this->offset = 10;
		}
		//if(68<=i && i<=71){
			//this->offset = 5;
		//}
	}
}

void CharacterImage::setPosition(int x,int y){
	//TODO bien esto
	float scale = 2;
	y = y  + 34*scale;//29 + 11;
	int y_legs = y - this->currentLegClip->h*scale;
	int y_torso = y_legs - this->currentClip->h*scale + this->offset*scale;
	int x_torso = x;
	int x_legs = x;
	if(goingLeft){
		x_torso = x_torso - this->currentClip->w*scale + 30*scale; // 30 width chabon
		x_legs = x_legs - this->currentLegClip->w*scale + 30*scale;
	}
	this->texture->setPosition(x_torso,y_torso);
	this->legs->setPosition(x_legs,y_legs);
}


void CharacterImage::setLegSprites(){

	// STILL

	gLegClips[0].x = 130;
	gLegClips[0].y = 1537;
	gLegClips[0].w = 21;
	gLegClips[0].h = 16;

	// MOVING	LAS 18 POSICIONES

	gLegClips[1].x = 255;
	gLegClips[1].y = 1533;
	gLegClips[1].w = 24;
	gLegClips[1].h = 21;

	gLegClips[2].x = 279;
	gLegClips[2].y = 1533;
	gLegClips[2].w = 30;
	gLegClips[2].h = 21;

	gLegClips[3].x = 310;
	gLegClips[3].y = 1533;
	gLegClips[3].w = 33;
	gLegClips[3].h = 21;

	gLegClips[4].x = 345;
	gLegClips[4].y = 1533;
	gLegClips[4].w = 20;
	gLegClips[4].h = 21;

	gLegClips[5].x = 366;
	gLegClips[5].y = 1533;
	gLegClips[5].w = 18;
	gLegClips[5].h = 21;

	gLegClips[6].x = 384;
	gLegClips[6].y = 1533;
	gLegClips[6].w = 18;
	gLegClips[6].h = 21;

	gLegClips[7].x = 404;
	gLegClips[7].y = 1533;
	gLegClips[7].w = 22;
	gLegClips[7].h = 21;

	gLegClips[8].x = 427;
	gLegClips[8].y = 1533;
	gLegClips[8].w = 27;
	gLegClips[8].h = 21;

	gLegClips[9].x = 456;
	gLegClips[9].y = 1533;
	gLegClips[9].w = 33;
	gLegClips[9].h = 21;

	gLegClips[10].x = 491;
	gLegClips[10].y = 1533;
	gLegClips[10].w = 20;
	gLegClips[10].h = 21;

	gLegClips[11].x = 512;
	gLegClips[11].y = 1533;
	gLegClips[11].w = 17;
	gLegClips[11].h = 21;

	gLegClips[12].x = 529;
	gLegClips[12].y = 1533;
	gLegClips[12].w = 19;
	gLegClips[12].h = 21;

	gLegClips[13].x = 551;
	gLegClips[13].y = 1533;
	gLegClips[13].w = 21;
	gLegClips[13].h = 21;

	gLegClips[14].x = 575;
	gLegClips[14].y = 1533;
	gLegClips[14].w = 26;
	gLegClips[14].h = 21;

	gLegClips[15].x = 602;
	gLegClips[15].y = 1533;
	gLegClips[15].w = 15;
	gLegClips[15].h = 21;

	gLegClips[16].x = 621;
	gLegClips[16].y = 1533;
	gLegClips[16].w = 19;
	gLegClips[16].h = 21;

	gLegClips[17].x = 643;
	gLegClips[17].y = 1533;
	gLegClips[17].w = 28;
	gLegClips[17].h = 21;

	gLegClips[18].x = 673;
	gLegClips[18].y = 1533;
	gLegClips[18].w = 19;
	gLegClips[18].h = 21;

	// INVISIBLE

	gLegClips[19].x = 139;
	gLegClips[19].y = 149+28;
	gLegClips[19].w = 29;
	gLegClips[19].h = 5;

	//LEFT

	// STILL

	gLegClips[20].x = 2381;
	gLegClips[20].y = 1537;
	gLegClips[20].w = 21;
	gLegClips[20].h = 16;

	// MOVING	LAS 18 POSICIONES

	gLegClips[21].x = 2255;
	gLegClips[21].y = 1533;
	gLegClips[21].w = 24;
	gLegClips[21].h = 21;

	gLegClips[22].x = 2224;
	gLegClips[22].y = 1533;
	gLegClips[22].w = 30;
	gLegClips[22].h = 21;

	gLegClips[23].x = 2190;
	gLegClips[23].y = 1533;
	gLegClips[23].w = 33;
	gLegClips[23].h = 21;

	gLegClips[24].x = 2168;
	gLegClips[24].y = 1533;
	gLegClips[24].w = 20;
	gLegClips[24].h = 21;

	gLegClips[25].x = 2150;
	gLegClips[25].y = 1533;
	gLegClips[25].w = 18;
	gLegClips[25].h = 21;

	gLegClips[26].x = 2131;
	gLegClips[26].y = 1533;
	gLegClips[26].w = 18;
	gLegClips[26].h = 21;

	gLegClips[27].x = 2107;
	gLegClips[27].y = 1533;
	gLegClips[27].w = 22;
	gLegClips[27].h = 21;

	gLegClips[28].x = 2078;
	gLegClips[28].y = 1533;
	gLegClips[28].w = 27;
	gLegClips[28].h = 21;

	gLegClips[29].x = 2044;
	gLegClips[29].y = 1533;
	gLegClips[29].w = 33;
	gLegClips[29].h = 21;

	gLegClips[30].x = 2021;
	gLegClips[30].y = 1533;
	gLegClips[30].w = 20;
	gLegClips[30].h = 21;

	gLegClips[31].x = 2004;
	gLegClips[31].y = 1533;
	gLegClips[31].w = 17;
	gLegClips[31].h = 21;

	gLegClips[32].x = 1984;
	gLegClips[32].y = 1533;
	gLegClips[32].w = 19;
	gLegClips[32].h = 21;

	gLegClips[33].x = 1960;
	gLegClips[33].y = 1533;
	gLegClips[33].w = 21;
	gLegClips[33].h = 21;

	gLegClips[34].x = 1932;
	gLegClips[34].y = 1533;
	gLegClips[34].w = 26;
	gLegClips[34].h = 21;

	gLegClips[35].x = 1915;
	gLegClips[35].y = 1533;
	gLegClips[35].w = 15;
	gLegClips[35].h = 21;

	gLegClips[36].x = 1892;
	gLegClips[36].y = 1533;
	gLegClips[36].w = 19;
	gLegClips[36].h = 21;

	gLegClips[37].x = 1862;
	gLegClips[37].y = 1533;
	gLegClips[37].w = 28;
	gLegClips[37].h = 21;

	gLegClips[38].x = 1842;
	gLegClips[38].y = 1533;
	gLegClips[38].w = 19;
	gLegClips[38].h = 21;

	// INVISIBLE

	gLegClips[39].x = 139;
	gLegClips[39].y = 149+28;
	gLegClips[39].w = 29;
	gLegClips[39].h = 5;


}

void CharacterImage::setSprites(){

	//IDLE

	gSpriteClips[0].x = 12;
	gSpriteClips[0].y = 8;
	gSpriteClips[0].w = 29;
	gSpriteClips[0].h = 29;

	gSpriteClips[1].x = 45;
	gSpriteClips[1].y = 8;
	gSpriteClips[1].w = 29;
	gSpriteClips[1].h = 29;

	gSpriteClips[2].x = 78;
	gSpriteClips[2].y = 8;
	gSpriteClips[2].w = 30;
	gSpriteClips[2].h = 28;

	gSpriteClips[3].x = 112;
	gSpriteClips[3].y = 9;
	gSpriteClips[3].w = 31;
	gSpriteClips[3].h = 27;

	//FIRE

	gSpriteClips[4].x = 227;
	gSpriteClips[4].y = 8;
	gSpriteClips[4].w = 50;
	gSpriteClips[4].h = 23;

	gSpriteClips[5].x = 281;
	gSpriteClips[5].y = 8;
	gSpriteClips[5].w = 51;
	gSpriteClips[5].h = 23;

	gSpriteClips[6].x = 336;
	gSpriteClips[6].y = 8;
	gSpriteClips[6].w = 50;
	gSpriteClips[6].h = 23;

	gSpriteClips[7].x = 393;
	gSpriteClips[7].y = 8;
	gSpriteClips[7].w = 37;
	gSpriteClips[7].h = 23;

	gSpriteClips[8].x = 436;
	gSpriteClips[8].y = 8;
	gSpriteClips[8].w = 37;
	gSpriteClips[8].h = 25;

	gSpriteClips[9].x = 478;
	gSpriteClips[9].y = 8;
	gSpriteClips[9].w = 37;
	gSpriteClips[9].h = 25;

	gSpriteClips[10].x = 519;
	gSpriteClips[10].y = 8;
	gSpriteClips[10].w = 37;
	gSpriteClips[10].h = 23;

	//LOOK_UP

	gSpriteClips[11].x = 1146;
	gSpriteClips[11].y = 8;
	gSpriteClips[11].w = 33;
	gSpriteClips[11].h = 25;

	gSpriteClips[12].x = 1146;
	gSpriteClips[12].y = 8;
	gSpriteClips[12].w = 33;
	gSpriteClips[12].h = 25;

	gSpriteClips[13].x = 1182;
	gSpriteClips[13].y = 8;
	gSpriteClips[13].w = 32;
	gSpriteClips[13].h = 24;

	gSpriteClips[14].x = 1182;
	gSpriteClips[14].y = 8;
	gSpriteClips[14].w = 32;
	gSpriteClips[14].h = 24;

	//IDLE UP

	gSpriteClips[15].x = 15;
	gSpriteClips[15].y = 57;
	gSpriteClips[15].w = 29;
	gSpriteClips[15].h = 26;

	gSpriteClips[16].x = 48;
	gSpriteClips[16].y = 58;
	gSpriteClips[16].w = 29;
	gSpriteClips[16].h = 26;

	gSpriteClips[17].x = 81;
	gSpriteClips[17].y = 57;
	gSpriteClips[17].w = 29;
	gSpriteClips[17].h = 26;

	gSpriteClips[18].x = 114;
	gSpriteClips[18].y = 57;
	gSpriteClips[18].w = 29;
	gSpriteClips[18].h = 26;

	//FIRE UP

	gSpriteClips[19].x = 143;
	gSpriteClips[19].y = 19;
	gSpriteClips[19].w = 22;
	gSpriteClips[19].h = 64;

	gSpriteClips[20].x = 173;
	gSpriteClips[20].y = 19;
	gSpriteClips[20].w = 22;
	gSpriteClips[20].h = 64;

	gSpriteClips[21].x = 199;
	gSpriteClips[21].y = 19;
	gSpriteClips[21].w = 22;
	gSpriteClips[21].h = 64;

	gSpriteClips[22].x = 225;
	gSpriteClips[22].y = 44;
	gSpriteClips[22].w = 22;
	gSpriteClips[22].h = 39;

	gSpriteClips[23].x = 251;
	gSpriteClips[23].y = 45;
	gSpriteClips[23].w = 25;
	gSpriteClips[23].h = 38;

	gSpriteClips[24].x = 280;
	gSpriteClips[24].y = 43;
	gSpriteClips[24].w = 25;
	gSpriteClips[24].h = 40;

	gSpriteClips[25].x = 365;
	gSpriteClips[25].y = 46;
	gSpriteClips[25].w = 26;
	gSpriteClips[25].h = 37;

	//RELOAD

	gSpriteClips[26].x = 15;
	gSpriteClips[26].y = 105;
	gSpriteClips[26].w = 33;
	gSpriteClips[26].h = 29;

	gSpriteClips[27].x = 51;
	gSpriteClips[27].y = 105;
	gSpriteClips[27].w = 35;
	gSpriteClips[27].h = 30;

	gSpriteClips[28].x = 89;
	gSpriteClips[28].y = 105;
	gSpriteClips[28].w = 35;
	gSpriteClips[28].h = 27;

	gSpriteClips[29].x = 127;
	gSpriteClips[29].y = 105;
	gSpriteClips[29].w = 36;
	gSpriteClips[29].h = 23;

	gSpriteClips[30].x = 166;
	gSpriteClips[30].y = 105;
	gSpriteClips[30].w = 36;
	gSpriteClips[30].h = 28;

	gSpriteClips[31].x = 206;
	gSpriteClips[31].y = 104;
	gSpriteClips[31].w = 36;
	gSpriteClips[31].h = 32;

	gSpriteClips[32].x = 245;
	gSpriteClips[32].y = 104;
	gSpriteClips[32].w = 36;
	gSpriteClips[32].h = 33;

	gSpriteClips[33].x = 284;
	gSpriteClips[33].y = 104;
	gSpriteClips[33].w = 36;
	gSpriteClips[33].h = 33;

	gSpriteClips[34].x = 324;
	gSpriteClips[34].y = 104;
	gSpriteClips[34].w = 37;
	gSpriteClips[34].h = 29;

	gSpriteClips[35].x = 365;
	gSpriteClips[35].y = 104;
	gSpriteClips[35].w = 35;
	gSpriteClips[35].h = 30;

	gSpriteClips[36].x = 403;
	gSpriteClips[36].y = 103;
	gSpriteClips[36].w = 35;
	gSpriteClips[36].h = 31;

	gSpriteClips[37].x = 441;
	gSpriteClips[37].y = 103;
	gSpriteClips[37].w = 35;
	gSpriteClips[37].h = 24;

	gSpriteClips[38].x = 480;
	gSpriteClips[38].y = 102;
	gSpriteClips[38].w = 35;
	gSpriteClips[38].h = 25;

	gSpriteClips[39].x = 519;
	gSpriteClips[39].y = 101;
	gSpriteClips[39].w = 38;
	gSpriteClips[39].h = 26;

	gSpriteClips[40].x = 561;
	gSpriteClips[40].y = 101;
	gSpriteClips[40].w = 38;
	gSpriteClips[40].h = 25;

	gSpriteClips[41].x = 603;
	gSpriteClips[41].y = 101;
	gSpriteClips[41].w = 38;
	gSpriteClips[41].h = 25;

	gSpriteClips[42].x = 646;
	gSpriteClips[42].y = 101;
	gSpriteClips[42].w = 39;
	gSpriteClips[42].h = 25;

	gSpriteClips[43].x = 684;
	gSpriteClips[43].y = 100;
	gSpriteClips[43].w = 41;
	gSpriteClips[43].h = 26;

	gSpriteClips[44].x = 733;
	gSpriteClips[44].y = 100;
	gSpriteClips[44].w = 39;
	gSpriteClips[44].h = 27;

	//CRAWLING

	gSpriteClips[45].x = 285;
	gSpriteClips[45].y = 230;
	gSpriteClips[45].w = 29;
	gSpriteClips[45].h = 39;

	gSpriteClips[46].x = 318;
	gSpriteClips[46].y = 228;
	gSpriteClips[46].w = 29;
	gSpriteClips[46].h = 41;

	gSpriteClips[47].x = 351;
	gSpriteClips[47].y = 234;
	gSpriteClips[47].w = 32;
	gSpriteClips[47].h = 26;

	gSpriteClips[48].x = 384;
	gSpriteClips[48].y = 243;
	gSpriteClips[48].w = 29;
	gSpriteClips[48].h = 26;

	gSpriteClips[49].x = 419;
	gSpriteClips[49].y = 243;
	gSpriteClips[49].w = 32;
	gSpriteClips[49].h = 26;

	gSpriteClips[50].x = 454;
	gSpriteClips[50].y = 243;
	gSpriteClips[50].w = 31;
	gSpriteClips[50].h = 26;

	gSpriteClips[51].x = 488;
	gSpriteClips[51].y = 243;
	gSpriteClips[51].w = 32;
	gSpriteClips[51].h = 26;

	gSpriteClips[52].x = 526;
	gSpriteClips[52].y = 245;
	gSpriteClips[52].w = 34;
	gSpriteClips[52].h = 24;

	//CRAWL IDLE

	gSpriteClips[53].x = 563;
	gSpriteClips[53].y = 245;
	gSpriteClips[53].w = 33;
	gSpriteClips[53].h = 24;

	gSpriteClips[54].x = 599;
	gSpriteClips[54].y = 245;
	gSpriteClips[54].w = 33;
	gSpriteClips[54].h = 24;

	gSpriteClips[55].x = 635;
	gSpriteClips[55].y = 245;
	gSpriteClips[55].w = 33;
	gSpriteClips[55].h = 24;

	gSpriteClips[56].x = 671;
	gSpriteClips[56].y = 245;
	gSpriteClips[56].w = 34;
	gSpriteClips[56].h = 24;

	//CRAWL SHOOT

	gSpriteClips[57].x = 683;
	gSpriteClips[57].y = 232;
	gSpriteClips[57].w = 50;
	gSpriteClips[57].h = 27;

	gSpriteClips[58].x = 736;
	gSpriteClips[58].y = 282;
	gSpriteClips[58].w = 51;
	gSpriteClips[58].h = 27;

	gSpriteClips[59].x = 790;
	gSpriteClips[59].y = 282;
	gSpriteClips[59].w = 50;
	gSpriteClips[59].h = 27;

	gSpriteClips[60].x = 845;
	gSpriteClips[60].y = 282;
	gSpriteClips[60].w = 37;
	gSpriteClips[60].h = 27;

	gSpriteClips[61].x = 885;
	gSpriteClips[61].y = 280;
	gSpriteClips[61].w = 37;
	gSpriteClips[61].h = 29;

	gSpriteClips[62].x = 925;
	gSpriteClips[62].y = 280;
	gSpriteClips[62].w = 37;
	gSpriteClips[62].h = 29;

	gSpriteClips[63].x = 965;
	gSpriteClips[63].y = 282;
	gSpriteClips[63].w = 37;
	gSpriteClips[63].h = 27;

	// CHANGING FROM WEAPON

	gSpriteClips[64].x = 1184;
	gSpriteClips[64].y = 99;
	gSpriteClips[64].w = 26;
	gSpriteClips[64].h = 34;

	gSpriteClips[65].x = 1184;
	gSpriteClips[65].y = 99;
	gSpriteClips[65].w = 26;
	gSpriteClips[65].h = 34;

	gSpriteClips[66].x = 1151;
	gSpriteClips[66].y = 98;
	gSpriteClips[66].w = 30;
	gSpriteClips[66].h = 36;

	gSpriteClips[67].x = 1151;
	gSpriteClips[67].y = 98;
	gSpriteClips[67].w = 30;
	gSpriteClips[67].h = 36;

	gSpriteClips[68].x = 1117;
	gSpriteClips[68].y = 99;
	gSpriteClips[68].w = 31;
	gSpriteClips[68].h = 26;

	gSpriteClips[69].x = 1117;
	gSpriteClips[69].y = 99;
	gSpriteClips[69].w = 31;
	gSpriteClips[69].h = 26;

	//CHANGING TO WEAPON (Doble Frame para que sea mas lento)

	gSpriteClips[70].x = 1117;
	gSpriteClips[70].y = 99;
	gSpriteClips[70].w = 31;
	gSpriteClips[70].h = 26;

	gSpriteClips[71].x = 1117;
	gSpriteClips[71].y = 99;
	gSpriteClips[71].w = 31;
	gSpriteClips[71].h = 26;

	gSpriteClips[72].x = 1151;
	gSpriteClips[72].y = 98;
	gSpriteClips[72].w = 30;
	gSpriteClips[72].h = 36;

	gSpriteClips[73].x = 1151;
	gSpriteClips[73].y = 98;
	gSpriteClips[73].w = 30;
	gSpriteClips[73].h = 36;

	gSpriteClips[74].x = 1184;
	gSpriteClips[74].y = 99;
	gSpriteClips[74].w = 26;
	gSpriteClips[74].h = 34;

	gSpriteClips[75].x = 1184;
	gSpriteClips[75].y = 99;
	gSpriteClips[75].w = 26;
	gSpriteClips[75].h = 34;

	//
	// SHOTGUN
	//

	//IDLE

	gSpriteClips[76].x = 1;
	gSpriteClips[76].y = 478;
	gSpriteClips[76].w = 37;
	gSpriteClips[76].h = 27;

	gSpriteClips[77].x = 41;
	gSpriteClips[77].y = 477;
	gSpriteClips[77].w = 38;
	gSpriteClips[77].h = 28;

	gSpriteClips[78].x = 82;
	gSpriteClips[78].y = 477;
	gSpriteClips[78].w = 38;
	gSpriteClips[78].h = 29;

	gSpriteClips[79].x = 124;
	gSpriteClips[79].y = 477;
	gSpriteClips[79].w = 38;
	gSpriteClips[79].h = 29;

	//FIRE

	gSpriteClips[80].x = 1013;
	gSpriteClips[80].y = 514;
	gSpriteClips[80].w = 60;
	gSpriteClips[80].h = 27;

	gSpriteClips[81].x = 1076;
	gSpriteClips[81].y = 515;
	gSpriteClips[81].w = 60;
	gSpriteClips[81].h = 27;

	gSpriteClips[82].x = 1202;
	gSpriteClips[82].y = 515;
	gSpriteClips[82].w = 60;
	gSpriteClips[82].h = 26;

	gSpriteClips[83].x = 914;
	gSpriteClips[83].y = 515;
	gSpriteClips[83].w = 43;
	gSpriteClips[83].h = 28;

	gSpriteClips[84].x = 959;
	gSpriteClips[84].y = 515;
	gSpriteClips[84].w = 43;
	gSpriteClips[84].h = 28;

	gSpriteClips[85].x = 822;
	gSpriteClips[85].y = 514;
	gSpriteClips[85].w = 44;
	gSpriteClips[85].h = 29;

	gSpriteClips[86].x = 869;
	gSpriteClips[86].y = 514;
	gSpriteClips[86].w = 42;
	gSpriteClips[86].h = 29;

	//LOOK UP 4 y son 2 repetidos

	gSpriteClips[87].x = 956;
	gSpriteClips[87].y = 465;
	gSpriteClips[87].w = 29;
	gSpriteClips[87].h = 37;

	gSpriteClips[88].x = 956;
	gSpriteClips[88].y = 465;
	gSpriteClips[88].w = 29;
	gSpriteClips[88].h = 37;

	gSpriteClips[89].x = 988;
	gSpriteClips[89].y = 460;
	gSpriteClips[89].w = 26;
	gSpriteClips[89].h = 41;

	gSpriteClips[90].x = 988;
	gSpriteClips[90].y = 460;
	gSpriteClips[90].w = 26;
	gSpriteClips[90].h = 41;

	// IDLE UP

	gSpriteClips[91].x = 575;
	gSpriteClips[91].y = 623;
	gSpriteClips[91].w = 22;
	gSpriteClips[91].h = 49;

	gSpriteClips[92].x = 600;
	gSpriteClips[92].y = 624;
	gSpriteClips[92].w = 22;
	gSpriteClips[92].h = 48;

	gSpriteClips[93].x = 808;
	gSpriteClips[93].y = 624;
	gSpriteClips[93].w = 22;
	gSpriteClips[93].h = 48;

	gSpriteClips[94].x = 783;
	gSpriteClips[94].y = 625;
	gSpriteClips[94].w = 22;
	gSpriteClips[94].h = 47;

	// FIRE UP

	gSpriteClips[95].x = 30;
	gSpriteClips[95].y = 554;
	gSpriteClips[95].w = 22;
	gSpriteClips[95].h = 69;

	gSpriteClips[96].x = 56;
	gSpriteClips[96].y = 552;
	gSpriteClips[96].w = 22;
	gSpriteClips[96].h = 71;

	gSpriteClips[97].x = 106;
	gSpriteClips[97].y = 551;
	gSpriteClips[97].w = 24;
	gSpriteClips[97].h = 72;

	gSpriteClips[98].x = 1184;
	gSpriteClips[98].y = 626;
	gSpriteClips[98].w = 23;
	gSpriteClips[98].h = 45;

	gSpriteClips[99].x = 1154;
	gSpriteClips[99].y = 630;
	gSpriteClips[99].w = 27;
	gSpriteClips[99].h = 41;

	gSpriteClips[100].x = 1122;
	gSpriteClips[100].y = 633;
	gSpriteClips[100].w = 30;
	gSpriteClips[100].h = 38;

	gSpriteClips[101].x = 1088;
	gSpriteClips[101].y = 623;
	gSpriteClips[101].w = 31;
	gSpriteClips[101].h = 48;

	// RELOADING

	gSpriteClips[102].x = 397;
	gSpriteClips[102].y = 474;
	gSpriteClips[102].w = 37;
	gSpriteClips[102].h = 27;

	gSpriteClips[103].x = 437;
	gSpriteClips[103].y = 474;
	gSpriteClips[103].w = 38;
	gSpriteClips[103].h = 28;

	gSpriteClips[104].x = 478;
	gSpriteClips[104].y = 474;
	gSpriteClips[104].w = 37;
	gSpriteClips[104].h = 28;

	gSpriteClips[105].x = 521;
	gSpriteClips[105].y = 475;
	gSpriteClips[105].w = 37;
	gSpriteClips[105].h = 27;

	gSpriteClips[106].x = 561;
	gSpriteClips[106].y = 475;
	gSpriteClips[106].w = 37;
	gSpriteClips[106].h = 27;

	gSpriteClips[107].x = 363;
	gSpriteClips[107].y = 468;
	gSpriteClips[107].w = 29;
	gSpriteClips[107].h = 36;

	gSpriteClips[108].x = 397;
	gSpriteClips[108].y = 474;
	gSpriteClips[108].w = 37;
	gSpriteClips[108].h = 27;

	gSpriteClips[109].x = 437;
	gSpriteClips[109].y = 474;
	gSpriteClips[109].w = 38;
	gSpriteClips[109].h = 28;

	gSpriteClips[110].x = 478;
	gSpriteClips[110].y = 474;
	gSpriteClips[110].w = 37;
	gSpriteClips[110].h = 28;

	gSpriteClips[111].x = 521;
	gSpriteClips[111].y = 475;
	gSpriteClips[111].w = 37;
	gSpriteClips[111].h = 27;

	gSpriteClips[112].x = 561;
	gSpriteClips[112].y = 475;
	gSpriteClips[112].w = 37;
	gSpriteClips[112].h = 27;

	gSpriteClips[113].x = 166;
	gSpriteClips[113].y = 469;
	gSpriteClips[113].w = 30;
	gSpriteClips[113].h = 36;

	gSpriteClips[114].x = 199;
	gSpriteClips[114].y = 469;
	gSpriteClips[114].w = 29;
	gSpriteClips[114].h = 36;

	gSpriteClips[115].x = 231;
	gSpriteClips[115].y = 469;
	gSpriteClips[115].w = 29;
	gSpriteClips[115].h = 36;

	gSpriteClips[116].x = 263;
	gSpriteClips[116].y = 469;
	gSpriteClips[116].w = 29;
	gSpriteClips[116].h = 36;

	gSpriteClips[117].x = 297;
	gSpriteClips[117].y = 469;
	gSpriteClips[117].w = 31;
	gSpriteClips[117].h = 36;

	gSpriteClips[118].x = 331;
	gSpriteClips[118].y = 469;
	gSpriteClips[118].w = 29;
	gSpriteClips[118].h = 36;

	gSpriteClips[119].x = 363;
	gSpriteClips[119].y = 468;
	gSpriteClips[119].w = 29;
	gSpriteClips[119].h = 36;

	gSpriteClips[120].x = 363;
	gSpriteClips[120].y = 468;
	gSpriteClips[120].w = 29;
	gSpriteClips[120].h = 36;


	// CRAWLING

	gSpriteClips[121].x = 648;
	gSpriteClips[121].y = 777;
	gSpriteClips[121].w = 39;
	gSpriteClips[121].h = 39;

	gSpriteClips[122].x = 690;
	gSpriteClips[122].y = 775;
	gSpriteClips[122].w = 39;
	gSpriteClips[122].h = 41;

	gSpriteClips[123].x = 733;
	gSpriteClips[123].y = 778;
	gSpriteClips[123].w = 40;
	gSpriteClips[123].h = 38;

	gSpriteClips[124].x = 19;
	gSpriteClips[124].y = 833;
	gSpriteClips[124].w = 24;
	gSpriteClips[124].h = 26;

	gSpriteClips[125].x = 53;
	gSpriteClips[125].y = 835;
	gSpriteClips[125].w = 41;
	gSpriteClips[125].h = 24;

	gSpriteClips[126].x = 97;
	gSpriteClips[126].y = 835;
	gSpriteClips[126].w = 41;
	gSpriteClips[126].h = 24;

	gSpriteClips[127].x = 141;
	gSpriteClips[127].y = 835;
	gSpriteClips[127].w = 41;
	gSpriteClips[127].h = 24;

	gSpriteClips[128].x = 185;
	gSpriteClips[128].y = 835;
	gSpriteClips[128].w = 41;
	gSpriteClips[128].h = 24;

	// CRAWL IDLE

	gSpriteClips[129].x = 361;
	gSpriteClips[129].y = 835;
	gSpriteClips[129].w = 41;
	gSpriteClips[129].h = 24;

	gSpriteClips[130].x = 405;
	gSpriteClips[130].y = 835;
	gSpriteClips[130].w = 41;
	gSpriteClips[130].h = 24;

	gSpriteClips[131].x = 449;
	gSpriteClips[131].y = 835;
	gSpriteClips[131].w = 41;
	gSpriteClips[131].h = 24;

	gSpriteClips[132].x = 493;
	gSpriteClips[132].y = 835;
	gSpriteClips[132].w = 41;
	gSpriteClips[132].h = 24;

	// CRAWL FIRE

	gSpriteClips[133].x = 542;
	gSpriteClips[133].y = 831;
	gSpriteClips[133].w = 67;
	gSpriteClips[133].h = 28;

	gSpriteClips[134].x = 613;
	gSpriteClips[134].y = 833;
	gSpriteClips[134].w = 67;
	gSpriteClips[134].h = 26;

	gSpriteClips[135].x = 754;
	gSpriteClips[135].y = 833;
	gSpriteClips[135].w = 67;
	gSpriteClips[135].h = 26;

	gSpriteClips[136].x = 825;
	gSpriteClips[136].y = 832;
	gSpriteClips[136].w = 44;
	gSpriteClips[136].h = 27;

	gSpriteClips[137].x = 872;
	gSpriteClips[137].y = 832;
	gSpriteClips[137].w = 44;
	gSpriteClips[137].h = 27;

	gSpriteClips[138].x = 919;
	gSpriteClips[138].y = 832;
	gSpriteClips[138].w = 44;
	gSpriteClips[138].h = 27;

	gSpriteClips[139].x = 966;
	gSpriteClips[139].y = 832;
	gSpriteClips[139].w = 44;
	gSpriteClips[139].h = 27;

	// CHANGING FROM WEAPON

	gSpriteClips[140].x = 982;
	gSpriteClips[140].y = 644;
	gSpriteClips[140].w = 31;
	gSpriteClips[140].h = 31;

	gSpriteClips[141].x = 982;
	gSpriteClips[141].y = 644;
	gSpriteClips[141].w = 31;
	gSpriteClips[141].h = 31;

	gSpriteClips[142].x = 919;
	gSpriteClips[142].y = 644;
	gSpriteClips[142].w = 27;
	gSpriteClips[142].h = 31;

	gSpriteClips[143].x = 919;
	gSpriteClips[143].y = 644;
	gSpriteClips[143].w = 27;
	gSpriteClips[143].h = 31;

	gSpriteClips[144].x = 881;
	gSpriteClips[144].y = 644;
	gSpriteClips[144].w = 35;
	gSpriteClips[144].h = 31;

	gSpriteClips[145].x = 881;
	gSpriteClips[145].y = 644;
	gSpriteClips[145].w = 35;
	gSpriteClips[145].h = 31;

	//CHANGING TO WEAPON (Doble Frame para que sea mas lento)

	gSpriteClips[146].x = 881;
	gSpriteClips[146].y = 644;
	gSpriteClips[146].w = 35;
	gSpriteClips[146].h = 31;

	gSpriteClips[147].x = 881;
	gSpriteClips[147].y = 644;
	gSpriteClips[147].w = 35;
	gSpriteClips[147].h = 31;

	gSpriteClips[148].x = 919;
	gSpriteClips[148].y = 644;
	gSpriteClips[148].w = 27;
	gSpriteClips[148].h = 31;

	gSpriteClips[149].x = 919;
	gSpriteClips[149].y = 644;
	gSpriteClips[149].w = 27;
	gSpriteClips[149].h = 31;

	gSpriteClips[150].x = 982;
	gSpriteClips[150].y = 644;
	gSpriteClips[150].w = 31;
	gSpriteClips[150].h = 31;

	gSpriteClips[151].x = 982;
	gSpriteClips[151].y = 644;
	gSpriteClips[151].w = 31;
	gSpriteClips[151].h = 31;

	// GENERIC

	//DYING

	gSpriteClips[152].x = 135;
	gSpriteClips[152].y = 3066;
	gSpriteClips[152].w = 31;
	gSpriteClips[152].h = 40;

	gSpriteClips[153].x = 169;
	gSpriteClips[153].y = 3066;
	gSpriteClips[153].w = 31;
	gSpriteClips[153].h = 40;

	gSpriteClips[154].x = 203;
	gSpriteClips[154].y = 3066;
	gSpriteClips[154].w = 30;
	gSpriteClips[154].h = 40;

	gSpriteClips[155].x = 237;
	gSpriteClips[155].y = 3066;
	gSpriteClips[155].w = 31;
	gSpriteClips[155].h = 40;

	gSpriteClips[156].x = 271;
	gSpriteClips[156].y = 3067;
	gSpriteClips[156].w = 32;
	gSpriteClips[156].h = 39;

	gSpriteClips[157].x = 305;
	gSpriteClips[157].y = 3069;
	gSpriteClips[157].w = 32;
	gSpriteClips[157].h = 37;

	gSpriteClips[158].x = 339;
	gSpriteClips[158].y = 3071;
	gSpriteClips[158].w = 29;
	gSpriteClips[158].h = 35;

	gSpriteClips[159].x = 370;
	gSpriteClips[159].y = 3073;
	gSpriteClips[159].w = 28;
	gSpriteClips[159].h = 33;

	gSpriteClips[160].x = 400;
	gSpriteClips[160].y = 3072;
	gSpriteClips[160].w = 27;
	gSpriteClips[160].h = 34;

	gSpriteClips[161].x = 430;
	gSpriteClips[161].y = 3074;
	gSpriteClips[161].w = 25;
	gSpriteClips[161].h = 32;

	gSpriteClips[162].x = 458;
	gSpriteClips[162].y = 3075;
	gSpriteClips[162].w = 24;
	gSpriteClips[162].h = 31;

	gSpriteClips[163].x = 486;
	gSpriteClips[163].y = 3077;
	gSpriteClips[163].w = 21;
	gSpriteClips[163].h = 29;

	gSpriteClips[164].x = 510;
	gSpriteClips[164].y = 3079;
	gSpriteClips[164].w = 22;
	gSpriteClips[164].h = 27;

	gSpriteClips[165].x = 536;
	gSpriteClips[165].y = 3081;
	gSpriteClips[165].w = 23;
	gSpriteClips[165].h = 25;

	gSpriteClips[166].x = 562;
	gSpriteClips[166].y = 3085;
	gSpriteClips[166].w = 27;
	gSpriteClips[166].h = 21;

	gSpriteClips[167].x = 592;
	gSpriteClips[167].y = 3090;
	gSpriteClips[167].w = 30;
	gSpriteClips[167].h = 16;

	gSpriteClips[168].x = 625;
	gSpriteClips[168].y = 3089;
	gSpriteClips[168].w = 34;
	gSpriteClips[168].h = 17;

	gSpriteClips[169].x = 662;
	gSpriteClips[169].y = 3090;
	gSpriteClips[169].w = 38;
	gSpriteClips[169].h = 16;


	//
	// LEFT
	//

	//IDLE

	gSpriteClips[170].x = 2492;
	gSpriteClips[170].y = 8;
	gSpriteClips[170].w = 29;
	gSpriteClips[170].h = 29;

	gSpriteClips[171].x = 2459;
	gSpriteClips[171].y = 8;
	gSpriteClips[171].w = 29;
	gSpriteClips[171].h = 29;

	gSpriteClips[172].x = 2425;
	gSpriteClips[172].y = 8;
	gSpriteClips[172].w = 30;
	gSpriteClips[172].h = 28;

	gSpriteClips[173].x = 2390;
	gSpriteClips[173].y = 9;
	gSpriteClips[173].w = 31;
	gSpriteClips[173].h = 27;

	//FIRE

	gSpriteClips[174].x = 2256;
	gSpriteClips[174].y = 8;
	gSpriteClips[174].w = 50;
	gSpriteClips[174].h = 23;

	gSpriteClips[175].x = 2200;
	gSpriteClips[175].y = 8;
	gSpriteClips[175].w = 51;
	gSpriteClips[175].h = 23;

	gSpriteClips[176].x = 2146;
	gSpriteClips[176].y = 8;
	gSpriteClips[176].w = 50;
	gSpriteClips[176].h = 23;

	gSpriteClips[177].x = 2102;
	gSpriteClips[177].y = 8;
	gSpriteClips[177].w = 37;
	gSpriteClips[177].h = 23;

	gSpriteClips[178].x = 2059;
	gSpriteClips[178].y = 8;
	gSpriteClips[178].w = 37;
	gSpriteClips[178].h = 25;

	gSpriteClips[179].x = 2017;
	gSpriteClips[179].y = 8;
	gSpriteClips[179].w = 37;
	gSpriteClips[179].h = 25;

	gSpriteClips[180].x = 1977;
	gSpriteClips[180].y = 8;
	gSpriteClips[180].w = 37;
	gSpriteClips[180].h = 23;

	//LOOK_UP

	gSpriteClips[181].x = 1352;
	gSpriteClips[181].y = 8;
	gSpriteClips[181].w = 33;
	gSpriteClips[181].h = 25;

	gSpriteClips[182].x = 1317;
	gSpriteClips[182].y = 8;
	gSpriteClips[182].w = 33;
	gSpriteClips[182].h = 25;

	gSpriteClips[183].x = 1284;
	gSpriteClips[183].y = 8;
	gSpriteClips[183].w = 32;
	gSpriteClips[183].h = 24;

	gSpriteClips[184].x = 1284;
	gSpriteClips[184].y = 8;
	gSpriteClips[184].w = 32;
	gSpriteClips[184].h = 24;

	//IDLE UP

	gSpriteClips[185].x = 2488;
	gSpriteClips[185].y = 57;
	gSpriteClips[185].w = 29;
	gSpriteClips[185].h = 26;

	gSpriteClips[186].x = 2455;
	gSpriteClips[186].y = 58;
	gSpriteClips[186].w = 29;
	gSpriteClips[186].h = 26;

	gSpriteClips[187].x = 2422;
	gSpriteClips[187].y = 57;
	gSpriteClips[187].w = 29;
	gSpriteClips[187].h = 26;

	gSpriteClips[188].x = 2389;
	gSpriteClips[188].y = 57;
	gSpriteClips[188].w = 29;
	gSpriteClips[188].h = 26;

	//FIRE UP

	gSpriteClips[189].x = 2363;
	gSpriteClips[189].y = 19;
	gSpriteClips[189].w = 22;
	gSpriteClips[189].h = 64;

	gSpriteClips[190].x = 2337;
	gSpriteClips[190].y = 19;
	gSpriteClips[190].w = 22;
	gSpriteClips[190].h = 64;

	gSpriteClips[191].x = 2311;
	gSpriteClips[191].y = 19;
	gSpriteClips[191].w = 22;
	gSpriteClips[191].h = 64;

	gSpriteClips[192].x = 2285;
	gSpriteClips[192].y = 44;
	gSpriteClips[192].w = 22;
	gSpriteClips[192].h = 39;

	gSpriteClips[193].x = 2256;
	gSpriteClips[193].y = 45;
	gSpriteClips[193].w = 25;
	gSpriteClips[193].h = 38;

	gSpriteClips[194].x = 2227;
	gSpriteClips[194].y = 43;
	gSpriteClips[194].w = 25;
	gSpriteClips[194].h = 40;

	gSpriteClips[195].x = 2200;
	gSpriteClips[195].y = 46;
	gSpriteClips[195].w = 26;
	gSpriteClips[195].h = 37;

	//RELOAD

	gSpriteClips[196].x = 2484;
	gSpriteClips[196].y = 105;
	gSpriteClips[196].w = 33;
	gSpriteClips[196].h = 29;

	gSpriteClips[197].x = 2246;
	gSpriteClips[197].y = 105;
	gSpriteClips[197].w = 35;
	gSpriteClips[197].h = 30;

	gSpriteClips[198].x = 2408;
	gSpriteClips[198].y = 105;
	gSpriteClips[198].w = 35;
	gSpriteClips[198].h = 27;

	gSpriteClips[199].x = 2369;
	gSpriteClips[199].y = 105;
	gSpriteClips[199].w = 36;
	gSpriteClips[199].h = 23;

	gSpriteClips[200].x = 2330;
	gSpriteClips[200].y = 105;
	gSpriteClips[200].w = 36;
	gSpriteClips[200].h = 28;

	gSpriteClips[201].x = 2290;
	gSpriteClips[201].y = 104;
	gSpriteClips[201].w = 36;
	gSpriteClips[201].h = 32;

	gSpriteClips[202].x = 2251;
	gSpriteClips[202].y = 104;
	gSpriteClips[202].w = 36;
	gSpriteClips[202].h = 33;

	gSpriteClips[203].x = 2212;
	gSpriteClips[203].y = 104;
	gSpriteClips[203].w = 36;
	gSpriteClips[203].h = 33;

	gSpriteClips[204].x = 2171;
	gSpriteClips[204].y = 104;
	gSpriteClips[204].w = 37;
	gSpriteClips[204].h = 29;

	gSpriteClips[205].x = 2132;
	gSpriteClips[205].y = 104;
	gSpriteClips[205].w = 35;
	gSpriteClips[205].h = 30;

	gSpriteClips[206].x = 2094;
	gSpriteClips[206].y = 103;
	gSpriteClips[206].w = 35;
	gSpriteClips[206].h = 31;

	gSpriteClips[207].x = 2056;
	gSpriteClips[207].y = 103;
	gSpriteClips[207].w = 35;
	gSpriteClips[207].h = 24;

	gSpriteClips[208].x = 2017;
	gSpriteClips[208].y = 102;
	gSpriteClips[208].w = 35;
	gSpriteClips[208].h = 25;

	gSpriteClips[209].x = 1975;
	gSpriteClips[209].y = 101;
	gSpriteClips[209].w = 38;
	gSpriteClips[209].h = 26;

	gSpriteClips[210].x = 1933;
	gSpriteClips[210].y = 101;
	gSpriteClips[210].w = 38;
	gSpriteClips[210].h = 25;

	gSpriteClips[211].x = 1891;
	gSpriteClips[211].y = 101;
	gSpriteClips[211].w = 38;
	gSpriteClips[211].h = 25;

	gSpriteClips[212].x = 1847;
	gSpriteClips[212].y = 101;
	gSpriteClips[212].w = 39;
	gSpriteClips[212].h = 25;

	gSpriteClips[213].x = 1802;
	gSpriteClips[213].y = 100;
	gSpriteClips[213].w = 41;
	gSpriteClips[213].h = 26;

	gSpriteClips[214].x = 1760;
	gSpriteClips[214].y = 100;
	gSpriteClips[214].w = 39;
	gSpriteClips[214].h = 27;

	//CRAWLING

	gSpriteClips[215].x = 2218;
	gSpriteClips[215].y = 230;
	gSpriteClips[215].w = 29;
	gSpriteClips[215].h = 39;

	gSpriteClips[216].x = 2185;
	gSpriteClips[216].y = 228;
	gSpriteClips[216].w = 29;
	gSpriteClips[216].h = 41;

	gSpriteClips[217].x = 2152;
	gSpriteClips[217].y = 234;
	gSpriteClips[217].w = 32;
	gSpriteClips[217].h = 26;

	gSpriteClips[218].x = 2216;
	gSpriteClips[218].y = 243;
	gSpriteClips[218].w = 29;
	gSpriteClips[218].h = 26;

	gSpriteClips[219].x = 2081;
	gSpriteClips[219].y = 243;
	gSpriteClips[219].w = 32;
	gSpriteClips[219].h = 26;

	gSpriteClips[220].x = 2047;
	gSpriteClips[220].y = 243;
	gSpriteClips[220].w = 31;
	gSpriteClips[220].h = 26;

	gSpriteClips[221].x = 2012;
	gSpriteClips[221].y = 243;
	gSpriteClips[221].w = 32;
	gSpriteClips[221].h = 26;

	gSpriteClips[222].x = 1972;
	gSpriteClips[222].y = 245;
	gSpriteClips[222].w = 34;
	gSpriteClips[222].h = 24;

	//CRAWL IDLE

	gSpriteClips[223].x = 1936;
	gSpriteClips[223].y = 245;
	gSpriteClips[223].w = 33;
	gSpriteClips[223].h = 24;

	gSpriteClips[224].x = 1900;
	gSpriteClips[224].y = 245;
	gSpriteClips[224].w = 33;
	gSpriteClips[224].h = 24;

	gSpriteClips[225].x = 1864;
	gSpriteClips[225].y = 245;
	gSpriteClips[225].w = 33;
	gSpriteClips[225].h = 24;

	gSpriteClips[226].x = 1872;
	gSpriteClips[226].y = 245;
	gSpriteClips[226].w = 34;
	gSpriteClips[226].h = 24;

	//CRAWL SHOOT

	gSpriteClips[227].x = 1799;
	gSpriteClips[227].y = 232;
	gSpriteClips[227].w = 50;
	gSpriteClips[277].h = 27;

	gSpriteClips[228].x = 1745;
	gSpriteClips[228].y = 282;
	gSpriteClips[228].w = 51;
	gSpriteClips[228].h = 27;

	gSpriteClips[229].x = 1690;
	gSpriteClips[229].y = 282;
	gSpriteClips[229].w = 50;
	gSpriteClips[229].h = 27;

	gSpriteClips[230].x = 1650;
	gSpriteClips[230].y = 282;
	gSpriteClips[230].w = 37;
	gSpriteClips[230].h = 27;

	gSpriteClips[231].x = 1610;
	gSpriteClips[231].y = 280;
	gSpriteClips[231].w = 37;
	gSpriteClips[231].h = 29;

	gSpriteClips[232].x = 1570;
	gSpriteClips[232].y = 280;
	gSpriteClips[232].w = 37;
	gSpriteClips[232].h = 29;

	gSpriteClips[233].x = 1530;
	gSpriteClips[233].y = 282;
	gSpriteClips[233].w = 37;
	gSpriteClips[233].h = 27;

	// CHANGING FROM WEAPON

	gSpriteClips[234].x = 1322;
	gSpriteClips[234].y = 99;
	gSpriteClips[234].w = 26;
	gSpriteClips[234].h = 34;

	gSpriteClips[235].x = 1322;
	gSpriteClips[235].y = 99;
	gSpriteClips[235].w = 26;
	gSpriteClips[235].h = 34;

	gSpriteClips[236].x = 1351;
	gSpriteClips[236].y = 98;
	gSpriteClips[236].w = 30;
	gSpriteClips[236].h = 36;

	gSpriteClips[237].x = 1351;
	gSpriteClips[237].y = 98;
	gSpriteClips[237].w = 30;
	gSpriteClips[237].h = 36;

	gSpriteClips[238].x = 1384;
	gSpriteClips[238].y = 99;
	gSpriteClips[238].w = 31;
	gSpriteClips[238].h = 26;

	gSpriteClips[239].x = 1384;
	gSpriteClips[239].y = 99;
	gSpriteClips[239].w = 31;
	gSpriteClips[239].h = 26;

	//CHANGING TO WEAPON (Doble Frame para que sea mas lento)

	gSpriteClips[240].x = 1384;
	gSpriteClips[240].y = 99;
	gSpriteClips[240].w = 31;
	gSpriteClips[240].h = 26;

	gSpriteClips[241].x = 1384;
	gSpriteClips[241].y = 99;
	gSpriteClips[241].w = 31;
	gSpriteClips[241].h = 26;

	gSpriteClips[242].x = 1351;
	gSpriteClips[242].y = 98;
	gSpriteClips[242].w = 30;
	gSpriteClips[242].h = 36;

	gSpriteClips[243].x = 1351;
	gSpriteClips[243].y = 98;
	gSpriteClips[243].w = 30;
	gSpriteClips[243].h = 36;

	gSpriteClips[244].x = 1322;
	gSpriteClips[244].y = 99;
	gSpriteClips[244].w = 26;
	gSpriteClips[244].h = 34;

	gSpriteClips[245].x = 1322;
	gSpriteClips[245].y = 99;
	gSpriteClips[245].w = 26;
	gSpriteClips[245].h = 34;

	//
	// SHOTGUN
	//

	//IDLE

	gSpriteClips[246].x = 2494;
	gSpriteClips[246].y = 478;
	gSpriteClips[246].w = 37;
	gSpriteClips[246].h = 27;

	gSpriteClips[247].x = 2453;
	gSpriteClips[247].y = 477;
	gSpriteClips[247].w = 38;
	gSpriteClips[247].h = 28;

	gSpriteClips[248].x = 2412;
	gSpriteClips[248].y = 477;
	gSpriteClips[248].w = 38;
	gSpriteClips[248].h = 29;

	gSpriteClips[249].x = 2370;
	gSpriteClips[249].y = 477;
	gSpriteClips[249].w = 38;
	gSpriteClips[249].h = 29;

	//FIRE

	gSpriteClips[250].x = 1459;
	gSpriteClips[250].y = 514;
	gSpriteClips[250].w = 60;
	gSpriteClips[250].h = 27;

	gSpriteClips[251].x = 1396;
	gSpriteClips[251].y = 515;
	gSpriteClips[251].w = 60;
	gSpriteClips[251].h = 27;

	gSpriteClips[252].x = 1270;
	gSpriteClips[252].y = 515;
	gSpriteClips[252].w = 60;
	gSpriteClips[252].h = 26;

	gSpriteClips[253].x = 1575;
	gSpriteClips[253].y = 515;
	gSpriteClips[253].w = 43;
	gSpriteClips[253].h = 28;

	gSpriteClips[254].x = 1530;
	gSpriteClips[254].y = 515;
	gSpriteClips[254].w = 43;
	gSpriteClips[254].h = 28;

	gSpriteClips[255].x = 1666;
	gSpriteClips[255].y = 514;
	gSpriteClips[255].w = 44;
	gSpriteClips[255].h = 29;

	gSpriteClips[256].x = 1621;
	gSpriteClips[256].y = 514;
	gSpriteClips[256].w = 42;
	gSpriteClips[256].h = 29;

	//LOOK UP 4 y son 2 repetidos

	gSpriteClips[257].x = 1447;
	gSpriteClips[257].y = 465;
	gSpriteClips[257].w = 29;
	gSpriteClips[257].h = 37;

	gSpriteClips[258].x = 1447;
	gSpriteClips[258].y = 465;
	gSpriteClips[258].w = 29;
	gSpriteClips[258].h = 37;

	gSpriteClips[259].x = 1518;
	gSpriteClips[259].y = 460;
	gSpriteClips[259].w = 26;
	gSpriteClips[259].h = 41;

	gSpriteClips[260].x = 1518;
	gSpriteClips[260].y = 460;
	gSpriteClips[260].w = 26;
	gSpriteClips[260].h = 41;

	// IDLE UP

	gSpriteClips[261].x = 1935;
	gSpriteClips[261].y = 623;
	gSpriteClips[261].w = 22;
	gSpriteClips[261].h = 49;

	gSpriteClips[262].x = 1910;
	gSpriteClips[262].y = 624;
	gSpriteClips[262].w = 22;
	gSpriteClips[262].h = 48;

	gSpriteClips[263].x = 1702;
	gSpriteClips[263].y = 624;
	gSpriteClips[263].w = 22;
	gSpriteClips[263].h = 48;

	gSpriteClips[264].x = 1727;
	gSpriteClips[264].y = 625;
	gSpriteClips[264].w = 22;
	gSpriteClips[264].h = 47;

	// FIRE UP

	gSpriteClips[265].x = 2480;
	gSpriteClips[265].y = 554;
	gSpriteClips[265].w = 22;
	gSpriteClips[265].h = 69;

	gSpriteClips[266].x = 2454;
	gSpriteClips[266].y = 552;
	gSpriteClips[266].w = 22;
	gSpriteClips[266].h = 71;

	gSpriteClips[267].x = 2402;
	gSpriteClips[267].y = 551;
	gSpriteClips[267].w = 24;
	gSpriteClips[267].h = 72;

	gSpriteClips[268].x = 1325;
	gSpriteClips[268].y = 626;
	gSpriteClips[268].w = 23;
	gSpriteClips[268].h = 45;

	gSpriteClips[269].x = 1352;
	gSpriteClips[269].y = 630;
	gSpriteClips[269].w = 27;
	gSpriteClips[269].h = 41;

	gSpriteClips[270].x = 1380;
	gSpriteClips[270].y = 633;
	gSpriteClips[270].w = 30;
	gSpriteClips[270].h = 38;

	gSpriteClips[271].x = 1413;
	gSpriteClips[271].y = 623;
	gSpriteClips[271].w = 31;
	gSpriteClips[271].h = 48;

	// RELOADING

	gSpriteClips[272].x = 2098;
	gSpriteClips[272].y = 474;
	gSpriteClips[272].w = 37;
	gSpriteClips[272].h = 27;

	gSpriteClips[273].x = 2057;
	gSpriteClips[273].y = 474;
	gSpriteClips[273].w = 38;
	gSpriteClips[273].h = 28;

	gSpriteClips[274].x = 2017;
	gSpriteClips[274].y = 474;
	gSpriteClips[274].w = 37;
	gSpriteClips[274].h = 28;

	gSpriteClips[275].x = 1974;
	gSpriteClips[275].y = 475;
	gSpriteClips[275].w = 37;
	gSpriteClips[275].h = 27;

	gSpriteClips[276].x = 1934;
	gSpriteClips[276].y = 475;
	gSpriteClips[276].w = 37;
	gSpriteClips[276].h = 27;

	gSpriteClips[277].x = 2140;
	gSpriteClips[277].y = 468;
	gSpriteClips[277].w = 29;
	gSpriteClips[277].h = 36;

	gSpriteClips[278].x = 2098;
	gSpriteClips[278].y = 474;
	gSpriteClips[278].w = 37;
	gSpriteClips[278].h = 27;

	gSpriteClips[279].x = 2057;
	gSpriteClips[279].y = 474;
	gSpriteClips[279].w = 38;
	gSpriteClips[279].h = 28;

	gSpriteClips[280].x = 2017;
	gSpriteClips[280].y = 474;
	gSpriteClips[280].w = 37;
	gSpriteClips[280].h = 28;

	gSpriteClips[281].x = 1974;
	gSpriteClips[281].y = 475;
	gSpriteClips[281].w = 37;
	gSpriteClips[281].h = 27;

	gSpriteClips[282].x = 1934;
	gSpriteClips[282].y = 475;
	gSpriteClips[282].w = 37;
	gSpriteClips[282].h = 27;

	gSpriteClips[283].x = 2336;
	gSpriteClips[283].y = 469;
	gSpriteClips[283].w = 30;
	gSpriteClips[283].h = 36;

	gSpriteClips[284].x = 2304;
	gSpriteClips[284].y = 469;
	gSpriteClips[284].w = 29;
	gSpriteClips[284].h = 36;

	gSpriteClips[285].x = 2272;
	gSpriteClips[285].y = 469;
	gSpriteClips[285].w = 29;
	gSpriteClips[285].h = 36;

	gSpriteClips[286].x = 2240;
	gSpriteClips[286].y = 469;
	gSpriteClips[286].w = 29;
	gSpriteClips[286].h = 36;

	gSpriteClips[287].x = 2204;
	gSpriteClips[287].y = 469;
	gSpriteClips[287].w = 31;
	gSpriteClips[287].h = 36;

	gSpriteClips[288].x = 2172;
	gSpriteClips[288].y = 469;
	gSpriteClips[288].w = 29;
	gSpriteClips[288].h = 36;

	gSpriteClips[289].x = 2140;
	gSpriteClips[289].y = 468;
	gSpriteClips[289].w = 29;
	gSpriteClips[289].h = 36;

	gSpriteClips[290].x = 2140;
	gSpriteClips[290].y = 468;
	gSpriteClips[290].w = 29;
	gSpriteClips[290].h = 36;


	// CRAWLING

	gSpriteClips[291].x = 1845;
	gSpriteClips[291].y = 777;
	gSpriteClips[291].w = 39;
	gSpriteClips[291].h = 39;

	gSpriteClips[292].x = 1803;
	gSpriteClips[292].y = 775;
	gSpriteClips[292].w = 39;
	gSpriteClips[292].h = 41;

	gSpriteClips[293].x = 1759;
	gSpriteClips[293].y = 778;
	gSpriteClips[293].w = 40;
	gSpriteClips[293].h = 38;

	gSpriteClips[294].x = 2489;
	gSpriteClips[294].y = 833;
	gSpriteClips[294].w = 24;
	gSpriteClips[294].h = 26;

	gSpriteClips[295].x = 2438;
	gSpriteClips[295].y = 835;
	gSpriteClips[295].w = 41;
	gSpriteClips[295].h = 24;

	gSpriteClips[296].x = 2394;
	gSpriteClips[296].y = 835;
	gSpriteClips[296].w = 41;
	gSpriteClips[296].h = 24;

	gSpriteClips[297].x = 2350;
	gSpriteClips[297].y = 835;
	gSpriteClips[297].w = 41;
	gSpriteClips[297].h = 24;

	gSpriteClips[298].x = 2306;
	gSpriteClips[298].y = 835;
	gSpriteClips[298].w = 41;
	gSpriteClips[298].h = 24;

	// CRAWL IDLE

	gSpriteClips[299].x = 2130;
	gSpriteClips[299].y = 835;
	gSpriteClips[299].w = 41;
	gSpriteClips[299].h = 24;

	gSpriteClips[300].x = 2086;
	gSpriteClips[300].y = 835;
	gSpriteClips[300].w = 41;
	gSpriteClips[300].h = 24;

	gSpriteClips[301].x = 2042;
	gSpriteClips[301].y = 835;
	gSpriteClips[301].w = 41;
	gSpriteClips[301].h = 24;

	gSpriteClips[302].x = 1998;
	gSpriteClips[302].y = 835;
	gSpriteClips[302].w = 41;
	gSpriteClips[302].h = 24;

	// CRAWL FIRE

	gSpriteClips[303].x = 1923;
	gSpriteClips[303].y = 831;
	gSpriteClips[303].w = 67;
	gSpriteClips[303].h = 28;

	gSpriteClips[304].x = 1852;
	gSpriteClips[304].y = 833;
	gSpriteClips[304].w = 67;
	gSpriteClips[304].h = 26;

	gSpriteClips[305].x = 1711;
	gSpriteClips[305].y = 833;
	gSpriteClips[305].w = 67;
	gSpriteClips[305].h = 26;

	gSpriteClips[306].x = 1663;
	gSpriteClips[306].y = 832;
	gSpriteClips[306].w = 44;
	gSpriteClips[306].h = 27;

	gSpriteClips[307].x = 1616;
	gSpriteClips[307].y = 832;
	gSpriteClips[307].w = 44;
	gSpriteClips[307].h = 27;

	gSpriteClips[308].x = 1569;
	gSpriteClips[308].y = 832;
	gSpriteClips[308].w = 44;
	gSpriteClips[308].h = 27;

	gSpriteClips[309].x = 1522;
	gSpriteClips[309].y = 832;
	gSpriteClips[309].w = 44;
	gSpriteClips[309].h = 27;

	// CHANGING FROM WEAPON

	gSpriteClips[310].x = 1481;
	gSpriteClips[310].y = 644;
	gSpriteClips[310].w = 31;
	gSpriteClips[310].h = 31;

	gSpriteClips[311].x = 1481;
	gSpriteClips[311].y = 644;
	gSpriteClips[311].w = 31;
	gSpriteClips[311].h = 31;

	gSpriteClips[312].x = 1553;
	gSpriteClips[312].y = 644;
	gSpriteClips[312].w = 27;
	gSpriteClips[312].h = 31;

	gSpriteClips[313].x = 1553;
	gSpriteClips[313].y = 644;
	gSpriteClips[313].w = 27;
	gSpriteClips[313].h = 31;

	gSpriteClips[314].x = 1586;
	gSpriteClips[314].y = 644;
	gSpriteClips[314].w = 35;
	gSpriteClips[314].h = 31;

	gSpriteClips[315].x = 1586;
	gSpriteClips[315].y = 644;
	gSpriteClips[315].w = 35;
	gSpriteClips[315].h = 31;

	//CHANGING TO WEAPON (Doble Frame para que sea mas lento)

	gSpriteClips[316].x = 1586;
	gSpriteClips[316].y = 644;
	gSpriteClips[316].w = 35;
	gSpriteClips[316].h = 31;

	gSpriteClips[317].x = 1586;
	gSpriteClips[317].y = 644;
	gSpriteClips[317].w = 35;
	gSpriteClips[317].h = 31;

	gSpriteClips[318].x = 1553;
	gSpriteClips[318].y = 644;
	gSpriteClips[318].w = 27;
	gSpriteClips[318].h = 31;

	gSpriteClips[319].x = 1553;
	gSpriteClips[319].y = 644;
	gSpriteClips[319].w = 27;
	gSpriteClips[319].h = 31;

	gSpriteClips[320].x = 1481;
	gSpriteClips[320].y = 644;
	gSpriteClips[320].w = 31;
	gSpriteClips[320].h = 31;

	gSpriteClips[321].x = 1481;
	gSpriteClips[321].y = 644;
	gSpriteClips[321].w = 31;
	gSpriteClips[321].h = 31;

	// GENERIC

	//DYING

	gSpriteClips[322].x = 2366;
	gSpriteClips[322].y = 3066;
	gSpriteClips[322].w = 31;
	gSpriteClips[322].h = 40;

	gSpriteClips[323].x = 2332;
	gSpriteClips[323].y = 3066;
	gSpriteClips[323].w = 31;
	gSpriteClips[323].h = 40;

	gSpriteClips[324].x = 2299;
	gSpriteClips[324].y = 3066;
	gSpriteClips[324].w = 30;
	gSpriteClips[324].h = 40;

	gSpriteClips[325].x = 2264;
	gSpriteClips[325].y = 3066;
	gSpriteClips[325].w = 31;
	gSpriteClips[325].h = 40;

	gSpriteClips[326].x = 2229;
	gSpriteClips[326].y = 3067;
	gSpriteClips[326].w = 32;
	gSpriteClips[326].h = 39;

	gSpriteClips[327].x = 2195;
	gSpriteClips[327].y = 3069;
	gSpriteClips[327].w = 32;
	gSpriteClips[327].h = 37;

	gSpriteClips[328].x = 2164;
	gSpriteClips[328].y = 3071;
	gSpriteClips[328].w = 29;
	gSpriteClips[328].h = 35;

	gSpriteClips[329].x = 2134;
	gSpriteClips[329].y = 3073;
	gSpriteClips[329].w = 28;
	gSpriteClips[329].h = 33;

	gSpriteClips[330].x = 2105;
	gSpriteClips[330].y = 3072;
	gSpriteClips[330].w = 27;
	gSpriteClips[330].h = 34;

	gSpriteClips[331].x = 2077;
	gSpriteClips[331].y = 3074;
	gSpriteClips[331].w = 25;
	gSpriteClips[331].h = 32;

	gSpriteClips[332].x = 2050;
	gSpriteClips[332].y = 3075;
	gSpriteClips[332].w = 24;
	gSpriteClips[332].h = 31;

	gSpriteClips[333].x = 2025;
	gSpriteClips[333].y = 3077;
	gSpriteClips[333].w = 21;
	gSpriteClips[333].h = 29;

	gSpriteClips[334].x = 2000;
	gSpriteClips[334].y = 3079;
	gSpriteClips[334].w = 22;
	gSpriteClips[334].h = 27;

	gSpriteClips[335].x = 1943;
	gSpriteClips[335].y = 3081;
	gSpriteClips[335].w = 23;
	gSpriteClips[335].h = 25;

	gSpriteClips[336].x = 1910;
	gSpriteClips[336].y = 3085;
	gSpriteClips[336].w = 27;
	gSpriteClips[336].h = 21;

	gSpriteClips[337].x = 1910;
	gSpriteClips[337].y = 3090;
	gSpriteClips[337].w = 30;
	gSpriteClips[337].h = 16;

	gSpriteClips[338].x = 1873;
	gSpriteClips[338].y = 3089;
	gSpriteClips[338].w = 34;
	gSpriteClips[338].h = 17;

	gSpriteClips[339].x = 1832;
	gSpriteClips[339].y = 3090;
	gSpriteClips[339].w = 38;
	gSpriteClips[339].h = 16;


}
