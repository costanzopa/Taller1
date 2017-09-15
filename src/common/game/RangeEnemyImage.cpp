/*
 * RangeEnemyImage.cpp
 *
 *  Created on: Nov 2, 2016
 *      Author: rodri
 */

#include "RangeEnemyImage.h"

namespace std {

RangeEnemyImage::RangeEnemyImage(SDL_Renderer* renderer,std::string path, float scale):EnemyImage(renderer,path,scale) {
	this->setSprites();

}
void RangeEnemyImage::setFrameProperties(int a){
	cout<<"Estas en range"<<a<<endl;
	if(a>=RENEMY_FRAMES){
		int frame = a - RENEMY_FRAMES;
		cout<<"Le restamos a a 	"<<frame<<endl;
		this->flip = SDL_FLIP_HORIZONTAL;
		this->currentClip = this->gSpriteClips+ frame;
	}else{
		this->flip = SDL_FLIP_NONE;
		this->currentClip = this->gSpriteClips+ a;
	}
}
void RangeEnemyImage::setPosition(int x,int y){
	int real_y = y + 41 - this->currentClip->h;
	this->texture->setPosition(x,real_y);
}
void RangeEnemyImage::render(){
	if(isDead)
			return;
	this->texture->render(currentClip,flip);
}
void RangeEnemyImage::setSprites(){

//WALKING

	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 26;
	gSpriteClips[0].h = 41;


	gSpriteClips[1].x = 50;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 26;
	gSpriteClips[1].h = 41;


	gSpriteClips[2].x = 103;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 26;
	gSpriteClips[2].h = 41;


	gSpriteClips[3].x = 163;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 29;
	gSpriteClips[3].h = 41;


	gSpriteClips[4].x = 227;
	gSpriteClips[4].y = 0;
	gSpriteClips[4].w = 31;
	gSpriteClips[4].h = 41;


	gSpriteClips[5].x = 284;
	gSpriteClips[5].y = 0;
	gSpriteClips[5].w = 29;
	gSpriteClips[5].h = 41;


	gSpriteClips[6].x = 342;
	gSpriteClips[6].y = 0;
	gSpriteClips[6].w = 27;
	gSpriteClips[6].h = 41;

	gSpriteClips[7].x = 4;
	gSpriteClips[7].y = 59;
	gSpriteClips[7].w = 22;
	gSpriteClips[7].h = 41;


	gSpriteClips[8].x = 60;
	gSpriteClips[8].y = 59;
	gSpriteClips[8].w = 24;
	gSpriteClips[8].h = 41;


	gSpriteClips[9].x = 117;
	gSpriteClips[9].y = 59;
	gSpriteClips[9].w = 26;
	gSpriteClips[9].h = 41;

//THINKING

	gSpriteClips[10].x = 182;
	gSpriteClips[10].y = 59;
	gSpriteClips[10].w = 23;
	gSpriteClips[10].h = 41;


	gSpriteClips[11].x = 238;
	gSpriteClips[11].y = 59;
	gSpriteClips[11].w = 22;
	gSpriteClips[11].h = 41;


	gSpriteClips[12].x = 298;
	gSpriteClips[12].y = 59;
	gSpriteClips[12].w = 21;
	gSpriteClips[12].h = 41;

//ATTACKING
	gSpriteClips[13].x = 7;
	gSpriteClips[13].y = 105;
	gSpriteClips[13].w = 21;
	gSpriteClips[13].h = 41;

	gSpriteClips[14].x = 64;
	gSpriteClips[14].y = 106;
	gSpriteClips[14].w = 20;
	gSpriteClips[14].h = 41;


	gSpriteClips[15].x = 120;
	gSpriteClips[15].y = 104;
	gSpriteClips[15].w = 23;
	gSpriteClips[15].h = 41;


	gSpriteClips[16].x = 186;
	gSpriteClips[16].y = 103;
	gSpriteClips[16].w = 24;
	gSpriteClips[16].h = 41;


	gSpriteClips[17].x = 242;
	gSpriteClips[17].y = 102;
	gSpriteClips[17].w = 24;
	gSpriteClips[17].h = 41;


	gSpriteClips[18].x = 297;
	gSpriteClips[18].y = 102;
	gSpriteClips[18].w = 25;
	gSpriteClips[18].h = 41;


	gSpriteClips[19].x = 340;
	gSpriteClips[19].y = 103;
	gSpriteClips[19].w = 26;
	gSpriteClips[19].h = 41;

	gSpriteClips[20].x = 6;
	gSpriteClips[20].y = 151;
	gSpriteClips[20].w = 27;
	gSpriteClips[20].h = 41;


	gSpriteClips[21].x = 59;
	gSpriteClips[21].y = 147;
	gSpriteClips[21].w = 34;
	gSpriteClips[21].h = 41;


	gSpriteClips[22].x = 115;
	gSpriteClips[22].y = 146;
	gSpriteClips[22].w = 37;
	gSpriteClips[22].h = 41;


	gSpriteClips[23].x = 177;
	gSpriteClips[23].y = 146;
	gSpriteClips[23].w = 41;
	gSpriteClips[23].h = 41;


	gSpriteClips[24].x = 235;
	gSpriteClips[24].y = 146;
	gSpriteClips[24].w = 37;
	gSpriteClips[24].h = 41;


	gSpriteClips[25].x = 284;
	gSpriteClips[25].y = 144;
	gSpriteClips[25].w = 33;
	gSpriteClips[25].h = 41;


	gSpriteClips[26].x = 330;
	gSpriteClips[26].y = 147;
	gSpriteClips[26].w = 33;
	gSpriteClips[26].h = 41;

	gSpriteClips[27].x = 3;
	gSpriteClips[27].y = 194;
	gSpriteClips[27].w = 33;
	gSpriteClips[27].h = 41;


	gSpriteClips[28].x = 51;
	gSpriteClips[28].y = 193;
	gSpriteClips[28].w = 34;
	gSpriteClips[28].h = 41;


	gSpriteClips[29].x = 110;
	gSpriteClips[29].y = 191;
	gSpriteClips[29].w = 31;
	gSpriteClips[29].h = 41;


	gSpriteClips[30].x = 171;
	gSpriteClips[30].y = 191;
	gSpriteClips[30].w = 26;
	gSpriteClips[30].h = 41;


	gSpriteClips[31].x = 231;
	gSpriteClips[31].y = 192;
	gSpriteClips[31].w = 26;
	gSpriteClips[31].h = 41;


	gSpriteClips[32].x = 282;
	gSpriteClips[32].y = 190;
	gSpriteClips[32].w = 26;
	gSpriteClips[32].h = 41;


	gSpriteClips[33].x = 334;
	gSpriteClips[33].y = 192;
	gSpriteClips[33].w = 29;
	gSpriteClips[33].h = 41;


	gSpriteClips[34].x = 6;
	gSpriteClips[34].y = 241;
	gSpriteClips[34].w = 33;
	gSpriteClips[34].h = 41;


	gSpriteClips[35].x = 49;
	gSpriteClips[35].y = 242;
	gSpriteClips[35].w = 47;
	gSpriteClips[35].h = 41;


	gSpriteClips[36].x = 110;
	gSpriteClips[36].y = 239;
	gSpriteClips[36].w = 32;
	gSpriteClips[36].h = 41;

	gSpriteClips[37].x = 174;
	gSpriteClips[37].y = 243;
	gSpriteClips[37].w = 29;
	gSpriteClips[37].h = 41;


	gSpriteClips[38].x = 232;
	gSpriteClips[38].y = 141;
	gSpriteClips[38].w = 29;
	gSpriteClips[38].h = 41;


	gSpriteClips[39].x = 282;
	gSpriteClips[39].y = 241;
	gSpriteClips[39].w = 22;
	gSpriteClips[39].h = 41;


//DYING


	gSpriteClips[40].x = 5;
	gSpriteClips[40].y = 288;
	gSpriteClips[40].w = 48;
	gSpriteClips[40].h = 63;


	gSpriteClips[41].x = 72;
	gSpriteClips[41].y = 288;
	gSpriteClips[41].w = 44;
	gSpriteClips[41].h = 63;


	gSpriteClips[42].x = 140;
	gSpriteClips[42].y = 288;
	gSpriteClips[42].w = 41;
	gSpriteClips[42].h = 63;


	gSpriteClips[43].x = 199;
	gSpriteClips[43].y = 188;
	gSpriteClips[43].w = 42;
	gSpriteClips[43].h = 63;


	gSpriteClips[44].x = 259;
	gSpriteClips[44].y = 288;
	gSpriteClips[44].w = 44;
	gSpriteClips[44].h = 63;


	gSpriteClips[45].x = 319;
	gSpriteClips[45].y = 288;
	gSpriteClips[45].w = 45;
	gSpriteClips[45].h = 63;


	gSpriteClips[46].x = 6;
	gSpriteClips[46].y = 355;
	gSpriteClips[46].w = 41;
	gSpriteClips[46].h = 63;

	gSpriteClips[47].x = 71;
	gSpriteClips[47].y = 355;
	gSpriteClips[47].w = 39;
	gSpriteClips[47].h = 63;


	gSpriteClips[48].x = 135;
	gSpriteClips[48].y = 355;
	gSpriteClips[48].w = 40;
	gSpriteClips[48].h = 63;


	gSpriteClips[49].x = 194;
	gSpriteClips[49].y = 355;
	gSpriteClips[49].w = 40;
	gSpriteClips[49].h = 63;

	gSpriteClips[50].x = 256;
	gSpriteClips[50].y = 355;
	gSpriteClips[50].w = 42;
	gSpriteClips[50].h = 63;


	gSpriteClips[51].x = 319;
	gSpriteClips[51].y = 355;
	gSpriteClips[51].w = 41;
	gSpriteClips[51].h = 63;


	gSpriteClips[52].x = 12;
	gSpriteClips[52].y = 429;
	gSpriteClips[52].w = 42;
	gSpriteClips[52].h = 63;


	gSpriteClips[53].x = 78;
	gSpriteClips[53].y = 429;
	gSpriteClips[53].w = 41;
	gSpriteClips[53].h = 63;


	gSpriteClips[54].x = 139;
	gSpriteClips[54].y = 429;
	gSpriteClips[54].w = 40;
	gSpriteClips[54].h = 63;


	gSpriteClips[55].x = 201;
	gSpriteClips[55].y = 429;
	gSpriteClips[55].w = 32;
	gSpriteClips[55].h = 63;


	gSpriteClips[56].x = 263;
	gSpriteClips[56].y = 429;
	gSpriteClips[56].w = 41;
	gSpriteClips[56].h = 63;

	gSpriteClips[57].x = 322;
	gSpriteClips[57].y = 429;
	gSpriteClips[57].w = 40;
	gSpriteClips[57].h = 63;


}

RangeEnemyImage::~RangeEnemyImage() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
