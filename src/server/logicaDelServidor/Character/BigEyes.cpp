/*
 * BigEyes.cpp
 *
 *  Created on: Nov 20, 2016
 *      Author: rodri
 */

#include "BigEyes.h"
#include <cstdlib>
#define HEIGHT 10
#define WIDTH 10

#define EYES_SPEED 30
#define LASER_WAIT 10
#define MOVING_OFFSET 0*EYES_SPEED
#define MOVING_OFFSET_LENGHT 1*EYES_SPEED

#define ATTACKING_OFFSET MOVING_OFFSET_LENGHT
#define ATTACKING_OFFSET_LENGTH 9*EYES_SPEED

#define ATTACK_SPEED 3
#define ATTACK_LENGTH 8*ATTACK_SPEED
#define EYE_RADIO 11
#define EYE_X_OFFSET 17
#define EYE_Y_OFFSET 15

#define PALLET_WIDTH 9
#define PALLET_HEIGHT 30
#define PALLET1_X_OFFSET 0
#define PALLET1_Y_OFFSET 0
#define PALLET2_X_OFFSET 26
#define PALLET2_Y_OFFSET 0

namespace std {

BigEyes::BigEyes(float scale,std::string ID,int vel,int dmg,int initial_pos,list<MainCharacter*>* target,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map):
		EnemyCharacter(scale,ID,vel,dmg,target,requestHandler,animsRequest,map) {
	//this->setIntroductionMessage(utils::NEW_BOSS);
	this->setExistingMessage(utils::EXISTING_BOSS);
	palletWidth=PALLET_WIDTH*scale;
	palletHeight=PALLET_HEIGHT*scale;
	eyeRadio= EYE_RADIO*scale;
	this->healthPoints = 50;
	sidePallet1= new CollisionRectangle(x,y,palletWidth,palletHeight,PALLET1_X_OFFSET*scale,PALLET1_Y_OFFSET*scale);
	sidePallet2= new CollisionRectangle(x,y,palletWidth,palletHeight,PALLET2_X_OFFSET*scale,PALLET2_Y_OFFSET*scale);
	eye = new CollisionElipse(x,y,eyeRadio,EYE_X_OFFSET*scale,EYE_Y_OFFSET*scale);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(eye);
	this->hitBox->addNewHitbox(sidePallet1);
	this->hitBox->addNewHitbox(sidePallet2);
	this->setActionsList();
	laserFrame = 0;
	laserCount = 0;
	firing = false;
	initialPosition = initial_pos;
	maxDistance = utils::SCREEN_WIDTH-100;
	positionToGo = initial_pos-((maxDistance)/2);
	cout<<"Inicio es	"<<initial_pos<<endl;
	cout<<"El destino es	"<<positionToGo<<endl;
	halfWalked = false;
	returned = false;
	sequence_selector=0;
	sequence_offset=0;
	attacking = false;
	direction = left;
}
void BigEyes::nextMove(){
	if(!appearedOnScreen)
		return;
	int i = std::rand() % 10000;
	if(i<20){
		this->dropBomb();
	}
	if(firing){
		if(!laserBullets){
			firing = false;
		}else if(!firingWait){
			this->shootLaser();
			firingWait = LASER_WAIT;
			laserBullets--;
		}else{
			firingWait--;
		}
	}else if(!attacking){

		laserCount += std::rand()%10;
		if(laserCount>500){
			laserCount = 0;
			attacking = true;
			this->selectCurrentSequence();
		}
	}
	if(!halfWalked){
		if(direction == left){
			this->x-=velocidad;
			this->hitBox->moveCollisionBox(this->x,this->y);
			if(this->x<=positionToGo){
				direction = right;
				positionToGo = initialPosition;
				halfWalked = true;
			}
			return;
		}
		this->x+=velocidad;
		this->hitBox->moveCollisionBox(this->x,this->y);
		if(this->x>=positionToGo){
			direction = left;
			positionToGo = initialPosition;
			halfWalked = true;
		}
		return;
	}
	if(!returned){
		if(direction == left){
			this->x-=velocidad;
			this->hitBox->moveCollisionBox(this->x,this->y);
			if(this->x<=positionToGo){
				direction = right;
				positionToGo = this->x+maxDistance;
				returned = true;
			}
			return;
		}
		this->x+=velocidad;
		this->hitBox->moveCollisionBox(this->x,this->y);
		if(this->x>=positionToGo){
			direction = left;
			positionToGo = this->x-maxDistance;
			returned = true;
		}
		return;
	}
	if(direction == left){
		this->x-=velocidad;
		this->hitBox->moveCollisionBox(this->x,this->y);
		if(this->x<=positionToGo){
			direction = right;
			positionToGo = this->x+(maxDistance)/2;
			returned = false;
			halfWalked = false;
		}
		return;
	}
	this->x+=velocidad;
	this->hitBox->moveCollisionBox(this->x,this->y);
	if(this->x>=positionToGo){
		direction = left;
		positionToGo = this->x-(maxDistance)/2;
		returned = false;
		halfWalked = false;
	}
	return;
	if(screenPosition > targetPosition){
		if(direction == right){
			direction = left;
		}
		this->hitBox->moveCollisionBox(this->x-velocidad,this->y);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			this->x -= velocidad;
			targetPosition = charTarget->getScreenPosition();
		}
		return;
	}else{
		if(direction == left){
			direction = right;
		}
		this->hitBox->moveCollisionBox(this->x+velocidad,this->y);
		if(this->collisionMap->moveAttemptCollisionable(this)){
			this->x += velocidad;
			targetPosition = charTarget->getScreenPosition();
		}
		return;
	}
}
std::string BigEyes::getFrame(){
		int frame = this->getFrameInt();
		int rayFrame = this->getExtraFrameInt();
		std::string frameString;
		std::stringstream out;
		out << frame;
		frameString.append(out.str());
		frameString.append(":");
		std::stringstream out1;
		out1 << rayFrame;
		frameString.append(out1.str());
		return frameString;
}
void BigEyes::startFiring(){
	//Dispara una cantidad aleatoria de disparos
	firing = true;
	laserBullets = 1 + std::rand()%5;
	firingWait =0;
}
int BigEyes::getExtraFrameInt(){
	if(attacking){
		int frame = laserFrame/ATTACK_SPEED;
		laserFrame++;
		if(laserFrame == ATTACK_LENGTH){
			laserFrame=0;
			this->startFiring();
			attacking = false;
		}
		return frame;
	}
	return 8;
	if(attacking){
			sequence_offset++;
			if(sequence_offset == ATTACKING_OFFSET_LENGTH){
				this->shootLaser();
				attacking = false;
				this->selectCurrentSequence();
				sequence_offset = 0;
			}
			return (sequence_offset+sequence_selector)/EYES_SPEED;
		}
		sequence_offset++;
		if(sequence_offset == MOVING_OFFSET_LENGHT)
			sequence_offset = 0;
		return (sequence_offset+sequence_selector)/EYES_SPEED;
}
void BigEyes::dropBomb(){
	this->playerActions->push_back(new BigEyeBomb(this->x+16*scale,this->y+16*scale,this->screenPosition,0,0,collisionMap,animsRequestHandler,this->characterID));
	this->requestHandler->addNewRequest(this->characterID);
}
int BigEyes::getXLaserVel(){
	int intentos=3;
	while(!this->charTarget->alive && intentos){
		this->setTarget();
		intentos--;
	}
		int dist = this->charTarget->x -this->x ;
		int caso = abs(dist)/25;
		switch(caso){
		case 0:
			if(dist>0)
				return 1;
			return -1;
		case 1:
			if(dist>0)
				return 1;
			return -1;
		case 2:
			if(dist>0)
				return 2;
			return -2;
		case 3:
			if(dist>0)
				return 2;
			return -2;
		case 4:
			if(dist>0)
				return 3;
			return -3;
		case 5:
			if(dist>0)
				return 3;
			return -3;
		}
		if(dist>0)
			return 4;
		return -4;
}
void BigEyes::shootLaser(){
	int xVel = this->getXLaserVel();
	int yVel = 3;
	this->playerActions->push_back(new EyeLaser(this->x+7,this->y+18,this->screenPosition,xVel,yVel,this->collisionMap,this->animsRequestHandler,this->characterID));
	this->requestHandler->addNewRequest(this->characterID);
}

void BigEyes::selectCurrentSequence(){
	sequence_selector = 0;
	if(attacking){
		sequence_selector+= ATTACKING_OFFSET;
	}
}
int BigEyes::getFrameInt(){
	if(!alive){
			this->dead=true;
			this->setExistingMessage(utils::DYING_ENEMY);
	}
	int intentos=3;
	while(!this->charTarget->alive && intentos){
		this->setTarget();
		intentos--;
	}
	int dist = this->x -this->charTarget->x;
	int caso = abs(dist)/50;
	switch(caso){
	case 0:
		if(dist>0)
			return 9;
		return 8;
	case 1:
		if(dist>0)
			return 10;
		return 7;
	case 2:
		if(dist>0)
			return 11;
		return 6;
	case 3:
		if(dist>0)
			return 12;
		return 5;
	case 4:
		if(dist>0)
			return 13;
		return 4;
	case 5:
		if(dist>0)
			return 14;
		return 3;
	case 6:
		if(dist>0)
			return 15;
		return 2;
	case 7:
		if(dist>0)
			return 16;
		return 1;
	}
	if(dist>0)
		return 17;
	return 0;

}

BigEyes::~BigEyes() {
}

} /* namespace std */
