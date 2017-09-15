/*
 * RangeEnemy.cpp
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#include "RangeEnemy.h"
#include <cstdlib>
#define RANGE_SPEED 8
#define WALK_BEGIN RANGE_SPEED*3
#define RENEMY_HEIGHT_TORSO 33
#define RENEMY_WIDHT_TORSO 12
#define X_OFFSET_RIGHT_TORSO 7
#define Y_OFFSET_RIGHT_TORSO 2
#define RENEMY_HEIGHT_LEGS 12
#define RENEMY_WIDHT_LEGS 23
#define X_OFFSET_RIGHT_LEGS 0
#define Y_OFFSET_RIGHT_LEGS 31
#define SHOOTING_SPEED 2

#define MOVING_OFFSET 0
#define MOVING_LENGTH 10*RANGE_SPEED

#define THINKING_OFFSET 10
#define THINKING_LENGTH 3*RANGE_SPEED

#define ATTACKING_OFFSET 13
#define ATTACKING_LENGTH 27*SHOOTING_SPEED

#define DYING_OFFSET 40
#define DYING_LENGTH 18*RANGE_SPEED

#define LEFT_OFFSET 58


RangeEnemy::RangeEnemy(float scale,std::string ID,int vel,int rnge,int dmg,list<MainCharacter*>* target,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map)
:EnemyCharacter(scale,ID,vel,dmg,target,requestHandler, animsRequest,map) {
	shot_table = new vector<int>();
	this->longBodyHeight = this->scale*RENEMY_HEIGHT_TORSO;
	this->feetHeight = this->scale*RENEMY_HEIGHT_LEGS;
	this->longBodyWidth = this->scale*RENEMY_WIDHT_TORSO;
	this->feetWidth = this->scale*RENEMY_WIDHT_LEGS;
	longBody = new CollisionRectangle(x,y,longBodyWidth ,longBodyHeight ,X_OFFSET_RIGHT_TORSO*scale , Y_OFFSET_RIGHT_TORSO*scale);
	feet = new CollisionRectangle(x,y,feetWidth ,feetHeight ,X_OFFSET_RIGHT_LEGS *scale, Y_OFFSET_RIGHT_LEGS*scale);
	this->setCollisionBox();
	attacking = false;
	thinking= false;
	this->thinkingFrames = 0;
	this->attackingFrames = 0;
	this->movingFrames = 0;
	this->dyingFrames = 0;
	this->sequence_select=0;
	currDir = right;
	shotCapability =0;
	this->hitBox->addNewHitbox(longBody);
	this->hitBox->addNewHitbox(feet);
	range = rnge;
	this->aSetShotTable();

}
void RangeEnemy::aSetShotTable(){
	float coef = 0.01;
	int previous=0;
	for(int i=40;i>-40;i-=8){
		int next = 16-(int)(coef*i*i);
		int delta_y = next - previous;
		previous = next;
		shot_table->push_back(delta_y);
	}
}
void RangeEnemy::die(){
	this->alive = false;
	this->selectCurrentSequence();
	this->sequence_offset = 0;
}
void RangeEnemy::selectCurrentSequence(){
	sequence_select = 0;
	if(!alive){
		sequence_select = DYING_OFFSET;
	}else if(thinking){
		sequence_select = THINKING_OFFSET;
	}else if(attacking){
		sequence_select = ATTACKING_OFFSET;
	}else if(moving){
		sequence_select = MOVING_OFFSET;
	}
	if(currDir == left)
			sequence_select += LEFT_OFFSET;
}
int RangeEnemy::getFrameInt(){
	if(!alive){
		int frame = dyingFrames/RANGE_SPEED;
		dyingFrames++;
		if(dyingFrames == DYING_LENGTH){
			this->dead = true;;
			this->setExistingMessage(utils::DYING_ENEMY);
			this->selectCurrentSequence();
			this->sequence_offset = 0;
		}
		frame +=sequence_select;
		return frame;
	}
	if(thinking){
		movingFrames = 0;
		int frame = thinkingFrames/RANGE_SPEED;
		thinkingFrames++;
		if(thinkingFrames == THINKING_LENGTH){
			thinkingFrames = 0;
		}
		frame +=sequence_select;
		return frame;
	}
	if(attacking){
		int frame = attackingFrames/SHOOTING_SPEED;
		if(frame==23)
			//Es el frame donde larga el moco
			this->shoot();
		attackingFrames++;
		if(attackingFrames == ATTACKING_LENGTH){
			movingFrames = 0;
			thinkingFrames = 0;
			this->attacking =false;
			attackingFrames = 0;
		}
		frame +=sequence_select;
		return frame;
	}
	//IF MOVING
	thinkingFrames = 0;
	int frame = movingFrames/RANGE_SPEED;
	movingFrames++;
	if(movingFrames == MOVING_LENGTH)
		movingFrames = 0;
	frame += sequence_select;
	return frame;
}

std::string RangeEnemy::getFrame(){
	int frame = this->getFrameInt();
	std::string frameString;
	std::stringstream out;
	out << frame;
	return out.str();
}
void RangeEnemy::shoot(){
	//cout<<shot_table->size()<<endl;
	playerActions->push_back(new ZombieShot(this->characterID,x,y,screenPosition,currDir,shot_table,collisionMap,animsRequestHandler));
	this->requestHandler->addNewRequest(this->characterID);

}
void RangeEnemy::nextMove(){
	int intentos=3;
	while(!this->charTarget->alive && intentos){
		this->setTarget();
		intentos--;
	}
	targetPosition = charTarget->x;
	if(!appearedOnScreen)
		return;
	if(attacking){
		return;
	}
	int distance = abs(this->x - targetPosition);
	if(this->x > targetPosition){
		//cout<<"Vamos a la izquierda"<<endl;
		if(currDir==right){
			//cout<<"Miramos a la izquierda"<<endl;
			this->currDir = left;
		}
		if(distance>range){
			moving = true;
			thinking = false;
			this->hitBox->moveCollisionBox(this->x-velocidad,this->y);
			if(this->collisionMap->moveAttemptCollisionable(this)){
				this->x -= velocidad;
			}else{
				this->hitBox->moveCollisionBox(this->x,this->y);
			}
		}else{
			moving = false;
			thinking = true;
			shotCapability += rand() % 10;
			if(shotCapability>350){
				thinking = false;
				this->attacking = true;
				shotCapability =0;
		}
			this->selectCurrentSequence();
		return;
		}
	}else if(this->x < targetPosition){
		if(currDir==left){
			currDir=right;
		}
		if(distance > range){
			moving = true;
			thinking = false;
			this->hitBox->moveCollisionBox(this->x+velocidad,this->y);
			if(this->collisionMap->moveAttemptCollisionable(this)){
				this->x += velocidad;
			}else{
				this->hitBox->moveCollisionBox(this->x,this->y);
			}
		}else{
			moving = false;
			thinking = true;
			shotCapability += rand() % 10;
			if(shotCapability>150){
				thinking = false;
				this->attacking = true;
				shotCapability =0;
		}
		this->selectCurrentSequence();
		return;
	}
	}
}
RangeEnemy::~RangeEnemy() {
	// TODO Auto-generated destructor stub
}

