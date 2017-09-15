/*
 * BigEyeBomb.cpp
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#include "BigEyeBomb.h"
#include <sstream>
#define BULLET_SPEED 3
#define BULLET_LENGTH BULLET_SPEED*8
#define DISSAPEAR_OFFSET 1
#define DISSAPEAR_SPEED 2
#define DISSAPEAR_LENGTH DISSAPEAR_SPEED*8
#define RADIO 5
#define X_OFFSET 6
#define Y_OFFSET 19
int BigEyeBomb::newId = 0;
BigEyeBomb::BigEyeBomb(int x,int y,int screenPosition,int dirX,int dirY,CollisionMap* map,AnimationsRequest* requester,std::string shooterID):id(newId++) {
	this->ID = shooterID;
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	this->y = y;
	this->x = x;
	shot = new CollisionElipse(x,y,RADIO,X_OFFSET,Y_OFFSET);
	this->setCollisionBox(); // Podria ser mas chico
	this->hitBox->addNewHitbox(shot);
	this->setCollisionMap(map);
	this->damage = 5;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::BIGEYES_BOMB);
	id.append(str);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->dissapearingFrames =0;
	//Tiene que empezar desde el 1 porque el 0 es la bala
	//this->dissapearingFrames = SMOKE_SPEED;
	this->bulletFrame =0;
	this->type.append(utils::BIGEYES_BOMB);
	this->screenPosition = screenPosition;
	this->setAnimationID(id);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	this->y_vel = 1;
	this->displacement = dirX;

}
std::string BigEyeBomb::getType(){
	return type;
}
bool BigEyeBomb::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool BigEyeBomb::collisionWith(EnemyCharacter* collided){
	return false;
}
bool BigEyeBomb::collisionWith(MainCharacter* collided){
	if(active){
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool BigEyeBomb::collisionWith(Animation* collided){
	return false;
}
bool BigEyeBomb::isConnected(){
	return inAction;
}
int BigEyeBomb::getDisplacement(){
	return this->displacement;
}
void BigEyeBomb::collisioned(Collisionable* a){
	return;
}
int BigEyeBomb::getLeftLimit(){
	return this->x;
}
int BigEyeBomb::getRightLimit(){
	return this->x +11;
}
std::string BigEyeBomb::getFrame(){
	if(!active){
		int frame = dissapearingFrames/DISSAPEAR_SPEED;
		this->dissapearingFrames++;
		if(dissapearingFrames == DISSAPEAR_LENGTH){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}
		frame += DISSAPEAR_OFFSET;
		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;
	}
	return "0";
}
void BigEyeBomb::nextPosition(){
	if(!active)
		return;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void BigEyeBomb::nextYPosition(){
	if(!active)
			return;
	this->y+=this->y_vel;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
int BigEyeBomb::getXPos(std::Parallax* gameBackground){
	if(dissapeared)
		return screenPosition;
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	this->nextPosition();
	if((this->screenPosition>utils::SCREEN_WIDTH || this->x < 0) && this->active){
			this->active = false;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	return screenPosition;
}
int BigEyeBomb::getYPos(){
	//cout<<"SS		"<<this->y<<endl;
	if(dissapeared)
			return this->y;
	this->nextYPosition();
	if(this->y<= 0){
		this->active = false;
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	if(this->y >= 480 && this->active){
			this->active = false;
			//this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	if(active)
		this->collisionMap->moveAttemptCollisionable(this);
	return this->y;
}
void BigEyeBomb::setDirection(int dir){

}
int BigEyeBomb::getId(){
	return this->id;
}
BigEyeBomb::~BigEyeBomb() {
	// TODO Auto-generated destructor stub
}

