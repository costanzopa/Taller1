/*
 * EnemyChaser.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: rodri
 */

#define EXPLOSION_SPEED 2
#define EXPLOSION_END 12
#define LOOP_SPEED 2
#define LOOP_END  LOOP_SPEED*2
#define DISSAPEAR_SPEED 3
#define DISSAPEAR_END DISSAPEAR_SPEED*6
#define ROCKET_WIDTH 21
#define ROCKET_HEIGHT 9
#define X_OFFSET 26
#define Y_OFFSET 3
#include "RocketShot.h"
#include <sstream>
int EnemyChaser::newId = 0;

namespace std {

EnemyChaser::EnemyChaser(int x,int y,int screenPosition,EnemyCharacter* enemy,CollisionMap* map,AnimationsRequest* requester,std::string guerrillaID ):id(newId++) {
	this->ID = guerrillaID;
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	shot = new CollisionRectangle(x,y,ROCKET_WIDTH,ROCKET_HEIGHT,X_OFFSET,Y_OFFSET);
	this->setCollisionBox();//x,y,51,15); // Arreglar
	this->hitBox->addNewHitbox(shot);
	this->x = x;
	this->setCollisionMap(map);
	this->damage = 50;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();

	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	//Tiene que empezar desde el 2 porque el 0 es el cohete
	this->dissapearingFrames = 0;
	this->loopingFrames = 0;
	this->y = y;
	this->type.append(utils::ROCKET_SHOT);
	this->screenPosition = screenPosition;
	this->setAnimationID(str);
	this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	speed = 10;
	this->target = enemy;
	this->wait = 1;
	this->displacement = speed;
	x_dir = left;
	firstFrame = true;
	this->setDirOffset();
}
std::string EnemyChaser::getType(){
	return type;
}
void EnemyChaser::setDirOffset(){
	if(this->x_dir == right)
		directionOffset = 0;
	else
		directionOffset = 8;
}
bool EnemyChaser::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool EnemyChaser::collisionWith(MainCharacter* collided){
	return false;
}
bool EnemyChaser::collisionWith(EnemyCharacter* collided){
	if(active){
		CharacterMap::addPoints(this->ID,100);
		collided->recieveDamage(this->damage);
		sequenceSelector= 2;
		this->active = false;
	}
	return false;
}
bool EnemyChaser::collisionWith(Animation* collided){
	return false;
}
bool EnemyChaser::isConnected(){
	return inAction;
}
int EnemyChaser::getDisplacement(){
	if(x_dir == left)
		return this->displacement;
	return -this->displacement;
}
void EnemyChaser::collisioned(Collisionable* a){
	return;
}
int EnemyChaser::getLeftLimit(){
	return this->x;
}
int EnemyChaser::getRightLimit(){
	return this->x+59;
}
std::string EnemyChaser::getFrame(){
	if(!active){
		int frame = dissapearingFrames/DISSAPEAR_SPEED;
		this->dissapearingFrames++;
		if(dissapearingFrames == DISSAPEAR_END){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}
		frame+=sequenceSelector+directionOffset;
		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;

	}
	int frame = loopingFrames/LOOP_SPEED;
	this->loopingFrames++;
	if(loopingFrames == LOOP_END){
		loopingFrames = 0;
	}
	frame +=directionOffset;
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
void EnemyChaser::nextPosition(){
	if(!active)
		return;
	wait--;
	if(wait == 0){
		cout << "Entro a fijarse a donde disparar el EC" << endl;
		this->searchPosition();
		this->setDirOffset();
		wait = 50;
	}
	if(this->x_dir == right)
		this->x += speed;
	else
		this->x -=speed;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void EnemyChaser::searchPosition(){
	if(this->target!=NULL){
		if(this->x < target->x){
			this->x_dir = right;
		}
		else{
			this->x_dir = left;
		}
	}
}
void EnemyChaser::nextYPosition(){
	return;
}
int EnemyChaser::getXPos(std::Parallax* gameBackground){
	if(dissapeared)
		return screenPosition;
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	this->nextPosition();
	if((this->screenPosition>utils::SCREEN_WIDTH || this->screenPosition < 0||this->x < 0) && this->active){
			this->active = false;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	return screenPosition;
}
int EnemyChaser::getYPos(){
	return this->y;
}
void EnemyChaser::setDirection(int dir){

}
int EnemyChaser::getId(){
	return this->id;
}
EnemyChaser::~EnemyChaser() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
