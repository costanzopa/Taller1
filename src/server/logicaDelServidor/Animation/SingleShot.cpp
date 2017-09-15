/*
 * SingleShot.cpp
 *
 *  Created on: 1/11/2016
 *      Author: usuario
 */
#define SMOKE_SPEED 2
#define SMOKE_END 12
#define RADIO 4
#define X_OFFSET 7
#define Y_OFFSET 9
#include "SingleShot.h"
#include <sstream>
int SingleShot::newId = 0;

SingleShot::SingleShot(int x,int y,int screenPosition,int dirX,int dirY,CollisionMap* map,AnimationsRequest* requester,std::string shooterID):id(newId++) {
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
	this->damage = 10;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::SINGLE_SHOT);
	id.append(str);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	//Tiene que empezar desde el 1 porque el 0 es la bala
	this->dissapearingFrames = SMOKE_SPEED;

	this->type.append(utils::SINGLE_SHOT);
	this->screenPosition = screenPosition;
	this->setAnimationID(id);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	speed = 6;
	if(dirX == 0)
		this->x_dir = right;
	else
		this->x_dir = left;
	if(dirY == 0)
		this->y_dir = horizontal;
	if(dirY == 1)
		this->y_dir = up;
	if(dirY == 2)
		this->y_dir = diagonal;
	if(y_dir!= up)
		this->displacement = speed;
	else
		this->displacement = 0;
}
std::string SingleShot::getType(){
	return type;
}
bool SingleShot::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool SingleShot::collisionWith(MainCharacter* collided){
	return false;
}
bool SingleShot::collisionWith(EnemyCharacter* collided){
	if(active){
		CharacterMap::addPoints(this->ID,30); //30 Puntos de Single Shot
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool SingleShot::collisionWith(Animation* collided){
	return false;
}
bool SingleShot::isConnected(){
	return inAction;
}
int SingleShot::getDisplacement(){
	if(x_dir == left)
		return this->displacement;
	return -this->displacement;
}
void SingleShot::collisioned(Collisionable* a){
	return;
}
int SingleShot::getLeftLimit(){
	return this->x;
}
int SingleShot::getRightLimit(){
	return this->x +16;
}
std::string SingleShot::getFrame(){
	if(!active){
		int frame = dissapearingFrames/SMOKE_SPEED;
		if(dissapearingFrames == SMOKE_END-1){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}
		this->dissapearingFrames++;
		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;

	}
	return "0";
}
void SingleShot::nextPosition(){
	if(!active)
		return;
	if(y_dir != up){
		if(this->x_dir == right)
			this->x += speed;
		else
			this->x -=speed;
	}
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void SingleShot::nextYPosition(){
	if(!active)
			return;
	if(this->y_dir != horizontal){
		this->y -= speed;
	}
	this->hitBox->moveCollisionBox(this->x,this->y);
}
int SingleShot::getXPos(std::Parallax* gameBackground){
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
int SingleShot::getYPos(){
	//cout<<"SS		"<<this->y<<endl;
	if(dissapeared)
			return this->y;
	this->nextYPosition();
	if(this->y<= 0){
		this->active = false;
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	if(active)
		this->collisionMap->moveAttemptCollisionable(this);
	return this->y;
}
void SingleShot::setDirection(int dir){

}
int SingleShot::SingleShot::getId(){
	return this->id;
}

SingleShot::~SingleShot() {
	// TODO Auto-generated destructor stub
}

