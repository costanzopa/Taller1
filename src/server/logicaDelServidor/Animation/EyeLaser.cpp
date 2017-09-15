/*
 * EyeLaser.cpp
 *
 *  Created on: 21/11/2016
 *      Author: usuario
 */

#include "EyeLaser.h"
#include <sstream>
#define BULLET_SPEED 3
#define BULLET_LENGTH BULLET_SPEED*8
#define DISSAPEAR_OFFSET 8
#define DISSAPEAR_SPEED 2
#define DISSAPEAR_LENGTH DISSAPEAR_SPEED*5
#define RADIO 5
#define X_OFFSET 5
#define Y_OFFSET 6
int EyeLaser::newId = 0;
EyeLaser::EyeLaser(int x,int y,int screenPosition,int dirX,int dirY,CollisionMap* map,AnimationsRequest* requester,std::string shooterID):id(newId++) {
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
	id.append(utils::BIGEYES_SHOT);
	id.append(str);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->dissapearingFrames =0;
	//Tiene que empezar desde el 1 porque el 0 es la bala
	//this->dissapearingFrames = SMOKE_SPEED;
	this->bulletFrame =0;
	this->type.append(utils::BIGEYES_SHOT);
	this->screenPosition = screenPosition;
	this->setAnimationID(id);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	this->x_vel = dirX;
	this->y_vel = dirY;
	this->displacement = dirX;

}
std::string EyeLaser::getType(){
	return type;
}
bool EyeLaser::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool EyeLaser::collisionWith(EnemyCharacter* collided){
	return false;
}
bool EyeLaser::collisionWith(MainCharacter* collided){
	if(active){
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool EyeLaser::collisionWith(Animation* collided){
	return false;
}
bool EyeLaser::isConnected(){
	return inAction;
}
int EyeLaser::getDisplacement(){
	return this->displacement;
}
void EyeLaser::collisioned(Collisionable* a){
	return;
}
int EyeLaser::getLeftLimit(){
	return this->x;
}
int EyeLaser::getRightLimit(){
	return this->x +11;
}
std::string EyeLaser::getFrame(){
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
	int frame = bulletFrame/BULLET_SPEED;
	bulletFrame++;
	if(bulletFrame==BULLET_LENGTH){
		bulletFrame=0;
	}
	std::string bulletFrameS;
	std::stringstream out;
	out << frame;
	bulletFrameS = out.str();
	return bulletFrameS;
}
void EyeLaser::nextPosition(){
	if(!active)
		return;
	this->x+=this->x_vel;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void EyeLaser::nextYPosition(){
	if(!active)
			return;
	this->y+=this->y_vel;
	if(y >= 550)
		this->active =false;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
int EyeLaser::getXPos(std::Parallax* gameBackground){
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
int EyeLaser::getYPos(){
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
void EyeLaser::setDirection(int dir){

}
int EyeLaser::getId(){
	return this->id;
}
EyeLaser::~EyeLaser() {
	// TODO Auto-generated destructor stub
}

