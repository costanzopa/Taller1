/*
 * UfoEnemy.cpp
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#include "UfoEnemy.h"
#include <sstream>
#define UFO_SPEED 3
#define SPAWN_OFFSET 12
#define SPAWN_LENGTH UFO_SPEED*8
#define UFO_LENGTH UFO_SPEED*11
#define HEAD_RADIO 12
#define	HEAD_X_OFFSET 25
#define HEAD_Y_OFFSET 12
#define	SIDE_RADIO 6
#define	SIDE1_X_OFFSET 8
#define	SIDE1_Y_OFFSET 21
#define SIDE2_X_OFFSET 43
#define SIDE2_Y_OFFSET 21
#define BODY_WIDTH 41
#define BODY_HEIGHT 13
#define BODY_X_OFFSET 6
#define BODY_Y_OFFSET 15


UfoEnemy::UfoEnemy(	float scale,list<EnemyCharacter*>* ufoSpawns,std::string ID,int vel,int dmg,list<MainCharacter*>* target,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map):
EnemyCharacter(scale,ID,vel,dmg,target,requestHandler,animsRequest,map){

	//this->setIntroductionMessage(utils::NEW_BOSS);
	this->healthPoints = 80;
	headRadio = HEAD_RADIO*scale;
	side1Radio= SIDE_RADIO*scale;
	side2Radio= SIDE_RADIO*scale;
	bodyWidth = BODY_WIDTH*scale;;
	bodyHeight = BODY_HEIGHT*scale;
	this->setExistingMessage(utils::EXISTING_BOSS);
	this->side1 = new CollisionElipse(x,y,side1Radio,SIDE1_X_OFFSET*scale,SIDE1_Y_OFFSET*scale);
	this->side2 = new CollisionElipse(x,y,side2Radio,SIDE2_X_OFFSET*scale,SIDE2_Y_OFFSET*scale);
	this->head = new CollisionElipse(x,y,headRadio,HEAD_X_OFFSET*scale,HEAD_Y_OFFSET*scale);
	this->body = new CollisionRectangle(x,y,bodyWidth,bodyHeight,BODY_X_OFFSET*scale,BODY_Y_OFFSET*scale);
	this->setCollisionBox();
	this->healthPoints = 100;
	this->hitBox->addNewHitbox(side1);
	this->hitBox->addNewHitbox(side2);
	this->hitBox->addNewHitbox(head);
	this->hitBox->addNewHitbox(body);
	this->firstTime = true;
	this->goLeft = true;
	this->spawning = false;
	this->frame = 0;
	this->spawnFrame = 0;
	counter = 1;
	this->spawns = ufoSpawns;
}
void UfoEnemy::nextMove(){
	if(!appearedOnScreen)
		return;

	if(this->firstTime) {
		this->initialPosition = this->x;
		this->firstTime = false;
	}

	if((this->x - this->initialPosition) > -200 && this->goLeft){
		this->x -= velocidad;
	}else{
		this->x += velocidad;
		this->goLeft = (this->x - this->initialPosition) > 200;
	}
	targetPosition = charTarget->getScreenPosition();
	this->collisionMap->moveAttemptCollisionable(this);
	//cout<<"Ufo		"<<this->y<<endl;
	this->hitBox->moveCollisionBox(this->x,this->y);
	return;
}

std::string UfoEnemy::getFrame(){
	if(!alive){
			this->dead=true;
			this->setExistingMessage(utils::DYING_ENEMY);
	}
	//El frame 11 es el qeu muestra la luz larga
	int spawn = 1 + ( std::rand() % (100) );
	if(appearedOnScreen && spawn == 10 && !this->spawns->empty()) {
		this->spawning = true;
	}

	int ret = this->frame/UFO_SPEED;
	this->frame++;
	if(this->frame==UFO_LENGTH)
			this->frame =0;
	stringstream s;
	s << ret;
	std::string frameString = s.str();
	frameString.append(":");
	if(spawning){
		int ret = this->spawnFrame/UFO_SPEED;
		if(this->spawnFrame == UFO_SPEED*6)
				this->spawnZombie();
		this->spawnFrame++;
		if(this->spawnFrame==SPAWN_LENGTH){
			this->spawnFrame =0;
			this->spawning = false;
		}
		stringstream a;
		a << ret;
		std::string ray = a.str();
		frameString.append(ray);
		return frameString;
	}
	frameString.append("9");
	return frameString;
}

void UfoEnemy::spawnZombie() {

	if(!this->spawns->empty()) {
		it = this->spawns->begin();
		EnemyCharacter* ec = *it;
		this->spawns->erase(it);
		ec->setCharacterPosition(this->x, this->y + 75);
	}

}
UfoEnemy::~UfoEnemy() {
	// TODO Auto-generated destructor stub
}


