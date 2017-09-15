/*
 * CannonShot.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: mario
 */

#include "CannonShot.h"
#include <sstream>
#define BULLET_SPEED 3
#define BULLET_LENGTH BULLET_SPEED*4
#define DISSAPEAR_OFFSET 5
#define DISSAPEAR_SPEED 2
#define DISSAPEAR_LENGTH DISSAPEAR_SPEED*13
#define RADIO 7
#define X_OFFSET_L 7
#define Y_OFFSET_L 8
#define X_OFFSET_R 39
#define Y_OFFSET_R 8
#define X_TRAIL_OFFSET_L 8
#define Y_TRAIL_OFFSET_L 3
#define X_TRAIL_OFFSET_R 3
#define Y_TRAIL_OFFSET_R 4
#define TRAIL_WIDTH 28
#define TRAIL_HEIGHT 11
#define RIGHT_OFFSET 17
int CannonShot::newId = 0;
CannonShot::CannonShot(int x,int y,int screenPosition,int dirX,int dirY,CollisionMap* map,AnimationsRequest* requester,std::string shooterID):id(newId++) {
	this->ID = shooterID;
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	this->y = y;
	this->x = x;
	if(dirX == 1){
			this->x_dir = right;
			this->sequence_select = 0;
			trail = new CollisionRectangle(x,y,TRAIL_WIDTH,TRAIL_HEIGHT,X_TRAIL_OFFSET_R,Y_TRAIL_OFFSET_R);
			shot = new CollisionElipse(x,y,RADIO,X_OFFSET_R,Y_OFFSET_R);
	}else{
			this->x_dir = left;
			this->sequence_select = RIGHT_OFFSET;
			trail = new CollisionRectangle(x,y,TRAIL_WIDTH,TRAIL_HEIGHT,X_TRAIL_OFFSET_L,Y_TRAIL_OFFSET_L);
			shot = new CollisionElipse(x,y,RADIO,X_OFFSET_L,Y_OFFSET_L);
	}
	this->setCollisionBox(); // Podria ser mas chico
	this->hitBox->addNewHitbox(shot);
	this->hitBox->addNewHitbox(trail);
	this->setCollisionMap(map);
	this->damage = 5;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::TANK_CANNON);
	id.append(str);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->dissapearingFrames =0;
	//Tiene que empezar desde el 1 porque el 0 es la bala
	//this->dissapearingFrames = SMOKE_SPEED;
	this->bulletFrame =0;
	this->type.append(utils::TANK_CANNON);
	this->screenPosition = screenPosition;
	this->setAnimationID(id);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	this->x_vel = dirX;
	this->y_vel = dirY;
	this->speed = 3;
	this->displacement = dirX;

}
std::string CannonShot::getType(){
	return type;
}
bool CannonShot::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool CannonShot::collisionWith(EnemyCharacter* collided){
	return false;
}
bool CannonShot::collisionWith(MainCharacter* collided){
	if(active){
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool CannonShot::collisionWith(Animation* collided){
	return false;
}
bool CannonShot::isConnected(){
	return inAction;
}
int CannonShot::getDisplacement(){
	return this->displacement;
}
void CannonShot::collisioned(Collisionable* a){
	return;
}
int CannonShot::getLeftLimit(){
	return this->x;
}
int CannonShot::getRightLimit(){
	return this->x +11;
}
std::string CannonShot::getFrame(){
	if(!active){
		int frame = dissapearingFrames/DISSAPEAR_SPEED;
		this->dissapearingFrames++;
		if(dissapearingFrames == DISSAPEAR_LENGTH){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}
		frame += DISSAPEAR_OFFSET;
		frame+=sequence_select;
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
	frame+=sequence_select;
	std::string bulletFrameS;
	std::stringstream out;
	out << frame;
	bulletFrameS = out.str();
	return bulletFrameS;
}
void CannonShot::nextPosition(){
	if(!active)
		return;
	if(this->x_dir)
		this->x+=this->speed;
	else
		this->x-=this->speed;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void CannonShot::nextYPosition(){
	if(!active)
			return;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
int CannonShot::getXPos(std::Parallax* gameBackground){
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
int CannonShot::getYPos(){
	if(dissapeared)
			return this->y;
	this->nextYPosition();
	if(this->y<= 0){
		this->active = false;
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	if(this->y >= 430 && this->active){
			this->active = false;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	if(active)
		this->collisionMap->moveAttemptCollisionable(this);
	return this->y;
}
void CannonShot::setDirection(int dir){

}
int CannonShot::getId(){
	return this->id;
}

CannonShot::~CannonShot() {
	// TODO Auto-generated destructor stub
}

