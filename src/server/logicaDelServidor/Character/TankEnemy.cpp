/*
 * MeleeEnemy.cpp
 *
 *  Created on: 31/10/2016
 *      Author: pablo
 */

#include "TankEnemy.h"
#include <cstdlib>
#include "../Animation/CannonShot.h"
#define TENEMY_HEIGHT_LONG 34
#define TENEMY_WIDHT_LONG 64
#define X_OFFSET_LEFT_LONG 4
#define Y_OFFSET_LEFT_LONG 20
#define X_OFFSET_RIGHT_LONG 4
#define Y_OFFSET_RIGHT_LONG 20
#define TENEMY_HEIGHT_SHORT 15
#define TENEMY_WIDHT_SHORT 40
#define X_OFFSET_LEFT_SHORT 16
#define Y_OFFSET_LEFT_SHORT 4
#define X_OFFSET_RIGHT_SHORT 15
#define Y_OFFSET_RIGHT_SHORT 4
#define TANK_SPEED 5
#define WALKING_OFFSET 2
#define WALKING_LENGTH 6*TANK_SPEED
#define TURNING_SPEED 3
#define TURNING_OFFSET 8
#define TURNING_LENGTH TURNING_SPEED*11
#define SHOOTING_SPEED 2
#define ATTACKING_OFFSET 19
#define ATTACKING_LENGTH 11*SHOOTING_SPEED
#define DYING_SPEED 2
#define DYING_OFFSET 30
#define DYING_LENGTH 25*DYING_SPEED
#define HEAVY_RELOAD 200
#define LIGHT_RELOAD 20


#define RIGHT_OFFSET 54

TankEnemy::TankEnemy(float scale,std::string ID,int vel,int dmg,list<MainCharacter*>* target,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map):
EnemyCharacter(scale,ID,vel,dmg,target,requestHandler,animsRequest,map){
	//this->setIntroductionMessage(utils::NEW_BOSS);
	this->setExistingMessage(utils::EXISTING_BOSS);
	tankWidth = TENEMY_WIDHT_LONG*scale;
	tankHeight =  TENEMY_WIDHT_LONG*scale;
	cannonWidth = TENEMY_WIDHT_SHORT*scale;
	cannonHeight = TENEMY_HEIGHT_SHORT*scale;
	this->healthPoints = 300;
	tank = new CollisionRectangle(x,y,tankWidth,tankHeight,X_OFFSET_LEFT_LONG*scale,Y_OFFSET_LEFT_LONG*scale);
	cannon = new CollisionRectangle(x,y,cannonWidth,cannonHeight,X_OFFSET_LEFT_SHORT*scale,Y_OFFSET_LEFT_SHORT*scale);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(tank);
	this->hitBox->addNewHitbox(cannon);
	sequence_selector=0;
	this->range = 300;
	this->movingFrames = 0;
	this->firingFrames = 0;
	this->turningFrames = 0;
	this->heavyWeaponReload = 0;
	this->lightWeaponReload = 0;
	sequence_offset=0;
	this->turning = false;
	attacking = false;
	direction = left;
}
void TankEnemy::nextMove(){
	if(!appearedOnScreen){
		this->idle = true;
		this->selectCurrentSequence();
		return;
	}
	if(appearedOnScreen)
		this->idle=false;
	cout<<"Estamos aca"<<endl;
	targetPosition = charTarget->x;
	if(this->heavyWeaponReload)
		this->heavyWeaponReload--;
	if(this->lightWeaponReload)
		this->lightWeaponReload--;
	int intentos=3;
	while(!this->charTarget->alive && intentos){
		this->setTarget();
		intentos--;
	}
	targetPosition = this->charTarget->x;
	if(this->turning || this->attacking){
		cout<<"we are attacking"<<endl;
		return;
	}
	if(abs(this->x-targetPosition)>this->range){
	cout<<"Estas muy lejos"<<endl;
	if(this->x > targetPosition){
		if(direction == right){
			this->tank->setOffset(X_OFFSET_LEFT_LONG*scale,Y_OFFSET_LEFT_LONG*scale);
			this->cannon->setOffset(X_OFFSET_LEFT_SHORT*scale,Y_OFFSET_LEFT_SHORT*scale);
			direction = left;
			this->turning = true;
			moving = false;
			this->selectCurrentSequence();
			return;
		}
		moving = true;
		this->selectCurrentSequence();
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
			this->tank->setOffset(X_OFFSET_RIGHT_LONG*scale,Y_OFFSET_RIGHT_LONG*scale);
			this->cannon->setOffset(X_OFFSET_RIGHT_SHORT*scale,Y_OFFSET_RIGHT_SHORT*scale);
			direction = right;
			this->turning = true;
			moving = false;
			this->selectCurrentSequence();
			return;
		}
		moving = true;
		this->selectCurrentSequence();
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
	}
	if(this->x > targetPosition){
		if(direction == right){
					this->tank->setOffset(X_OFFSET_LEFT_LONG*scale,Y_OFFSET_LEFT_LONG*scale);
					this->cannon->setOffset(X_OFFSET_LEFT_SHORT*scale,Y_OFFSET_LEFT_SHORT*scale);
					direction = left;
					this->turning = true;
					moving = false;
					this->selectCurrentSequence();
					return;
		}
	}else{
		if(direction == left){
			this->tank->setOffset(X_OFFSET_RIGHT_LONG*scale,Y_OFFSET_RIGHT_LONG*scale);
			this->cannon->setOffset(X_OFFSET_RIGHT_SHORT*scale,Y_OFFSET_RIGHT_SHORT*scale);
			direction = right;
			this->turning = true;
			moving = false;
			this->selectCurrentSequence();
			return;
		}

	}
		moving = false;
		turning = false;
		if(!heavyWeaponReload)
			this->shootCanon();
		if(!lightWeaponReload)
			this->shootLightWeapon();
		if(!attacking)
			idle = true;
		this->selectCurrentSequence();
}

void TankEnemy::shootCanon(){
	attacking = true;
	this->playerActions->push_back(new CannonShot(this->x,this->y,screenPosition,this->direction,0,collisionMap,animsRequestHandler,this->characterID));
	this->requestHandler->addNewRequest(this->characterID);
	this->heavyWeaponReload = HEAVY_RELOAD;
	cout<<"We shoot Heavy"<<endl;
}
void TankEnemy::shootLightWeapon(){
	attacking = true;
	this->lightWeaponReload = LIGHT_RELOAD;
	cout<<"We shoot Light"<<endl;
}
void TankEnemy::attack(){
	attacking = true;
	sequence_offset = 0;
	this->selectCurrentSequence();
	this->charTarget->recieveDamage(10000);
	return;
}

void TankEnemy::selectCurrentSequence(){
	if(moving)
		sequence_selector = WALKING_OFFSET;
	else if(attacking)
		sequence_selector = ATTACKING_OFFSET;
	else if(turning)
		sequence_selector =	TURNING_OFFSET;
	else if(idle)
		sequence_selector = 0;
	if(direction == right)
		sequence_selector += RIGHT_OFFSET;
}

std::string TankEnemy::getFrame(){
		int frame = this->getFrameInt();
		std::string frameString;
		std::stringstream out;
		out << frame;
		frameString.append(out.str());
		frameString.append(":0");
		return frameString;
}
int TankEnemy::getFrameInt(){
	if(!alive){
			this->dead=true;
			this->setExistingMessage(utils::DYING_ENEMY);
	}
	if(attacking){
		int frame = this->firingFrames/SHOOTING_SPEED;
		this->firingFrames++;
		frame += sequence_selector;
		if(firingFrames == ATTACKING_LENGTH){
			attacking = false;
			this->firingFrames =0;
			this->selectCurrentSequence();
		}

		return frame;
	}
	if(idle){
		int frame = sequence_selector;
		return frame;
	}
	if(turning){
		int frame = this->turningFrames/TURNING_SPEED;
		turningFrames++;
		frame += sequence_selector;
		if(turningFrames == TURNING_LENGTH){
			cout<<"Entramos aca AAAAAAAAAAAAAAAAAAAAAA"<<endl;
			turningFrames=0;
			turning = false;
			this->selectCurrentSequence();
		}
		return frame;
	}
	//IF WALKING
	int frame = this->movingFrames/TANK_SPEED;
	this->movingFrames++;
	frame += sequence_selector;
	if(movingFrames == WALKING_LENGTH)
		movingFrames = 0;
	return frame;
}

TankEnemy::~TankEnemy() {
	// TODO Auto-generated destructor stub
}

