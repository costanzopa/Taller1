/*
 * FlameShot.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: rodri
 */

#define EXPLOSION_SPEED 2
#define EXPLOSION_END 12

#define LOOPING_RADIO 10
#define LOOPING_X_OFFSET 29
#define LOOPING_Y_OFFSET 15
#define STARTING_RADIO 7
#define STARTING_X_OFFSET 15
#define STARTING_Y_OFFSET 5
#define FLAME_SPEED 4
#define DISSAPEAR_SPEED 2
#define INIT_END FLAME_SPEED*4
#define LOOP_END FLAME_SPEED*3
#define DISSAPEAR_END DISSAPEAR_SPEED*8
#include "FlameShot.h"
#include "RocketShot.h"
#include <sstream>
int FlameShot::newId = 0;

namespace std {

FlameShot::FlameShot(int x,int y,int screenPosition,int dirX,CollisionMap* map,AnimationsRequest* requester,string jediID):id(newId++) {
	this->ID = jediID;
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	startingShot = new CollisionElipse(x,y,STARTING_RADIO,STARTING_X_OFFSET,STARTING_Y_OFFSET);
	loopingShot = new CollisionElipse(x,y,LOOPING_RADIO,LOOPING_X_OFFSET,LOOPING_Y_OFFSET);
	secondaryBox = new CollisionBox();
	secondaryBox->addNewHitbox(loopingShot);
	this->setCollisionBox();//x,y,51,15); // Arreglar
	this->hitBox->addNewHitbox(startingShot);
	this->x = x;
	this->setCollisionMap(map);
	this->damage = 30;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	//Tiene que empezar desde el 2 porque el 0 es el cohete
	this->sequenceSelector = 0;
	this->dissapearingFrames =0;
	this->startingFrames =0;
	this->loopingFrames =0;
	this->y = y;
	this->type.append(utils::FLAME_SHOT);
	this->screenPosition = screenPosition;
	this->setAnimationID(str);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	speed = 2;
	if(dirX == 0)
		this->x_dir = right;
	else
		this->x_dir = left;
	this->displacement = speed;
	firstFrame = true;
}

std::string FlameShot::getType(){
	return type;
}
bool FlameShot::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool FlameShot::collisionWith(MainCharacter* collided){
	return false;
}
bool FlameShot::collisionWith(EnemyCharacter* collided){
	if(active){
		//cout<<"AWANTAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
		this->sequenceSelector = 7;
		CharacterMap::addPoints(this->ID,50);
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool FlameShot::collisionWith(Animation* collided){
	return false;
}
bool FlameShot::isConnected(){
	return inAction;
}
int FlameShot::getDisplacement(){
	if(x_dir == left)
		return this->displacement;
	return -this->displacement;
}
void FlameShot::collisioned(Collisionable* a){
	return;
}
int FlameShot::getLeftLimit(){
	return this->x;
}
int FlameShot::getRightLimit(){
	if(sequenceSelector==0)
		return this->x+35;
	return this->x+47;
}
std::string FlameShot::getFrame(){
	if(!active){
		int frame = dissapearingFrames/DISSAPEAR_SPEED;
		if(dissapearingFrames == DISSAPEAR_END-1){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}
		this->dissapearingFrames++;
		frame+= this->sequenceSelector;
		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;

	}
	if(sequenceSelector==0){
		int frame = this->startingFrames/FLAME_SPEED;
		this->startingFrames++;
		if(startingFrames == INIT_END){
			CollisionBox* aux = this->hitBox;
			this->hitBox = this->secondaryBox;
			this->secondaryBox = aux;
			this->hitBox->moveCollisionBox(this->x,this->y);
			sequenceSelector = 4;
		}
		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;
	}
	int frame = this->loopingFrames/FLAME_SPEED;
	this->loopingFrames++;
	if(this->loopingFrames == LOOP_END){
		loopingFrames = 0;
	}
	frame+=this->sequenceSelector;
	std::string bulletFrame;
	std::stringstream out;
	out << frame;
	bulletFrame = out.str();
	return bulletFrame;
	// He aqui el codigo mas feo que hayas visto en tu vida
	// Warning: No mirar
	if(firstFrame){
		firstFrame = false;
		return "0";
	}
	else{
		firstFrame = true;
		return "1";
	}
	// Fin del codigo feo
}
void FlameShot::nextPosition(){
	if(!active)
		return;
	if(this->x_dir == right)
		this->x += speed;
	else
		this->x -=speed;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void FlameShot::nextYPosition(){
	return;
}
int FlameShot::getXPos(std::Parallax* gameBackground){
	if(dissapeared)
		return screenPosition;
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	this->nextPosition();
	if((this->screenPosition>utils::SCREEN_WIDTH || this->screenPosition < 0-LOOPING_RADIO || this->x < 0) && this->active){
			this->active = false;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	return screenPosition;
}
int FlameShot::getYPos(){
	return this->y;
}
void FlameShot::setDirection(int dir){

}
int FlameShot::getId(){
	return this->id;
}
FlameShot::~FlameShot() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
