/*
 * MeleeEnemy.cpp
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#include "MeleeEnemy.h"
#include <cstdlib>
#define MELEE_SPEED 8
#define MENEMY_HEIGHT_LONG 37
#define MENEMY_WIDHT_LONG 13
#define X_OFFSET_LEFT_LONG 10
#define Y_OFFSET_LEFT_LONG 1
#define X_OFFSET_RIGHT_LONG 11
#define Y_OFFSET_RIGHT_LONG 1
#define MENEMY_HEIGHT_SHORT 27
#define MENEMY_WIDHT_SHORT 10
#define X_OFFSET_LEFT_SHORT 23
#define Y_OFFSET_LEFT_SHORT 8
#define X_OFFSET_RIGHT_SHORT 3
#define Y_OFFSET_RIGHT_SHORT 8
#define WALKING_OFFSET_LENGTH 14*MELEE_SPEED

#define MOVING_LENGTH 14*MELEE_SPEED

#define ATTACKING_OFFSET 14
#define ATTACKING_LENGTH 18*MELEE_SPEED

#define DYING_OFFSET 32
#define DEATH_SPEED 3
#define DEATH_LENGTH DEATH_SPEED*12

#define RIGHT_OFFSET 45

MeleeEnemy::MeleeEnemy(float scale,std::string ID,int vel,int dmg,list<MainCharacter*>* target,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map):
EnemyCharacter(scale,ID,vel,dmg,target,requestHandler,animsRequest,map){
	this->longBodyHeight = this->scale*MENEMY_HEIGHT_LONG;
	this->shortBodyHeight = this->scale*MENEMY_HEIGHT_SHORT;
	this->longBodyWidth = this->scale*MENEMY_WIDHT_LONG;
	this->shortBodyWidth = this->scale*MENEMY_WIDHT_SHORT;
	longBody = new CollisionRectangle(x,y,longBodyWidth,longBodyHeight,X_OFFSET_LEFT_LONG*scale,Y_OFFSET_LEFT_LONG*scale);
	shortBody = new CollisionRectangle(x,y,shortBodyWidth,shortBodyHeight,X_OFFSET_LEFT_SHORT*scale,Y_OFFSET_LEFT_SHORT*scale);
	this->setCollisionBox();
	deathFrame=0;
	this->hitBox->addNewHitbox(longBody);
	this->hitBox->addNewHitbox(shortBody);
	sequence_selector=0;
	this->deathFrame=0;
	this->attackingFrame =0;
	this->movingFrame=0;
	sequence_offset=0;
	attacking = false;
	direction = left;
}

void MeleeEnemy::startDeathAnimation(){
	this->setExistingMessage(utils::DYING_ENEMY);
}
void MeleeEnemy::nextMove(){
	int intentos=3;
	while(!this->charTarget->alive && intentos){
		this->setTarget();
		intentos--;
	}
	if(!appearedOnScreen)
		return;
	targetPosition = this->charTarget->x;
	if(attacking)
		return;
	if(abs(this->x-targetPosition)>30){
	if(this->x > targetPosition){
		if(direction == right){
			this->longBody->setOffset(X_OFFSET_LEFT_LONG*scale,Y_OFFSET_LEFT_LONG*scale);
			this->shortBody->setOffset(X_OFFSET_LEFT_SHORT*scale,Y_OFFSET_LEFT_SHORT*scale);
			direction = left;
			this->selectCurrentSequence();
		}
		this->hitBox->moveCollisionBox(this->x-velocidad,this->y);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			this->x -= velocidad;
		}else{
			//Si hay algo o alguien estorbando mi camino cambio de target
			this->setTarget();
			this->hitBox->moveCollisionBox(this->x,this->y);
		}
		return;
	}else{
		if(direction == left){
			this->longBody->setOffset(X_OFFSET_RIGHT_LONG*scale,Y_OFFSET_RIGHT_LONG*scale);
			this->shortBody->setOffset(X_OFFSET_RIGHT_SHORT*scale,Y_OFFSET_RIGHT_SHORT*scale);
			direction = right;
			this->selectCurrentSequence();
		}
		this->hitBox->moveCollisionBox(this->x+velocidad,this->y);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			this->x += velocidad;
		}else{
			//Si hay algo o alguien estorbando mi camino cambio de target
			this->setTarget();
			this->hitBox->moveCollisionBox(this->x,this->y);
		}
		return;
	}
	}else{
		this->attacking = true;
	}
}

void MeleeEnemy::attack(){
	if(direction== left)
		this->hitBox->moveCollisionBox(this->x-20,this->y);
	else
		this->hitBox->moveCollisionBox(this->x+20,this->y);
	if(this->hitBox->collisions(this->charTarget->hitBox))
		this->charTarget->recieveDamage(10000);
	this->hitBox->moveCollisionBox(this->x,this->y);
	return;
}

void MeleeEnemy::selectCurrentSequence(){
	sequence_selector = 0;
	if(direction == right)
		sequence_selector += RIGHT_OFFSET;
}

std::string MeleeEnemy::getFrame(){
		int frame = this->getFrameInt();
		std::string frameString;
		std::stringstream out;
		out << frame;
		return out.str();
}
int MeleeEnemy::getFrameInt(){
	if(!alive){
		int frame = deathFrame/DEATH_SPEED;
		deathFrame++;
		if(deathFrame == DEATH_LENGTH){
			this->dead=true;
			this->setExistingMessage(utils::DYING_ENEMY);
		}
		return DYING_OFFSET+frame+sequence_selector;
	}

	if(attacking){
		int frame = attackingFrame/MELEE_SPEED;
		attackingFrame++;
		if(frame == 12)
			this->attack();
		if(attackingFrame == ATTACKING_LENGTH){
			attacking = false;
			movingFrame = 0;
			attackingFrame = 0;
			this->selectCurrentSequence();
		}
		return frame+ATTACKING_OFFSET+sequence_selector;
	}
	//IF WALKING
	int frame = movingFrame/MELEE_SPEED;
	movingFrame++;
	if(movingFrame == MOVING_LENGTH)
		movingFrame = 0;
	return frame+sequence_selector;
}

MeleeEnemy::~MeleeEnemy() {
	// TODO Auto-generated destructor stub
}

