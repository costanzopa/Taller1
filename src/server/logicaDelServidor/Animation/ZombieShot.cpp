/*
 * ZombieShot.cpp
 *
 *  Created on: 18/11/2016
 *      Author: usuario
 */

#define SMOKE_SPEED 2
#define SMOKE_END 12
#define Y_SPEED 8
#define RADIO 4
#define X_OFFSET 4
#define Y_OFFSET 4
#define ANIMATION_SPEED 15
#include "ZombieShot.h"
#define ANIMATION_LENGTH 200
#define RIGHT_OFFSET 21
#define DISSAPEAR_OFFSET 13
#define DISSAPEAR_LENGTH SMOKE_SPEED*8
int ZombieShot::newId = 0;

ZombieShot::ZombieShot(std::string ID,int x,int y,int screenPosition,int dirX,std::vector<int>* table,CollisionMap* map,AnimationsRequest* requester):id(newId++) {
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	this->y = y;
	this->x = x;
	this->shot_table = table;
	shot = new CollisionElipse(x,y,RADIO,X_OFFSET,Y_OFFSET);
	this->setCollisionBox(); // Podria ser mas chico
	this->hitBox->addNewHitbox(shot);
	this->setCollisionMap(map);
	this->damage = 20;
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::ZOMBIE_SHOT);
	id = ID;
	id.append(str);
	hasToDescend = Y_SPEED;
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	//Tiene que empezar desde el 1 porque el 0 es la bala
	this->dissapearingFrames = 0;
	this->frameNumber =0;
	this->type.append(utils::ZOMBIE_SHOT);
	this->screenPosition = screenPosition;
	this->setAnimationID(id);
	//this->setAnimationImage("Images/characters/sprites-char-7.png");
	anchoPantalla = utils::SCREEN_WIDTH;
	speed = 2;
	if(dirX == 0){
		this->x_dir = right;
		sequence_selector = RIGHT_OFFSET;
	}
	else{
		this->x_dir = left;
		sequence_selector =0;
	}

	this->displacement = 0;
	this->current_y = y;
	this->shot_table_index = 0;
}

std::string ZombieShot::getType(){
	return type;
}
bool ZombieShot::collisionWith(Collisionable* collided){
	return collided->collisionWith(this);
}
bool ZombieShot::collisionWith(MainCharacter* collided){
	if(active){
		//cout<<"Activo la bala"<<endl;
		collided->recieveDamage(this->damage);
		this->active = false;
	}
	return false;
}
bool ZombieShot::collisionWith(EnemyCharacter* collided){
	return false;
}
bool ZombieShot::collisionWith(Animation* collided){
	return false;
}
bool ZombieShot::isConnected(){
	return inAction;
}
int ZombieShot::getDisplacement(){
	if(x_dir == left)
		return this->displacement;
	return -this->displacement;
}
void ZombieShot::collisioned(Collisionable* a){
	return;
}
int ZombieShot::getLeftLimit(){
	return this->x;
}
int ZombieShot::getRightLimit(){
	return this->x +16;
}
std::string ZombieShot::getFrame(){
	if(!active){
		int frame = dissapearingFrames/SMOKE_SPEED;
		this->dissapearingFrames++;
		frame+=sequence_selector;
		if(dissapearingFrames == DISSAPEAR_LENGTH){
			this->dissapeared = true;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
		}

		std::string bulletFrame;
		std::stringstream out;
		out << frame;
		bulletFrame = out.str();
		return bulletFrame;

	}
	int frame = this->getFrameInt();
	std::string bulletFrame;
	std::stringstream out;
	out << frame;
	bulletFrame = out.str();
	return bulletFrame;
}
int ZombieShot::getFrameInt(){
	int frame = this->frameNumber/ANIMATION_SPEED;
	this->frameNumber++;
	frame +=sequence_selector;
	if(frameNumber==ANIMATION_LENGTH){
		this->active = false;
		sequence_selector+=DISSAPEAR_OFFSET;
	}
	return frame;
}
void ZombieShot::nextPosition(){
	if(!active)
		return;
	if(this->x_dir == right)
		this->x += speed;
	else
		this->x -=speed;
	this->hitBox->moveCollisionBox(this->x,this->y);
}
void ZombieShot::moveNextHeight(){
	if(shot_table_index== shot_table->size()-1)
		return;
	shot_table_index++;

}
void ZombieShot::nextYPosition(){
	if(!active)
			return;
	if(hasToDescend==0){
		hasToDescend = Y_SPEED;
		this->y -= shot_table->at(shot_table_index);
		this->moveNextHeight();
	}else{
		hasToDescend--;
	}
	this->hitBox->moveCollisionBox(this->x,this->current_y);
}
int ZombieShot::getXPos(std::Parallax* gameBackground){
	if(dissapeared)
		return screenPosition;
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->nextPosition();
	this->collisionMap->moveAttemptCollisionable(this);
	if((this->screenPosition>utils::SCREEN_WIDTH || this->screenPosition == 0) && this->active){
			this->active = false;
			this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	return screenPosition;
}
int ZombieShot::getYPos(){
	if(dissapeared)
			return this->y;
	this->nextYPosition();
	if(active)
		this->collisionMap->moveAttemptCollisionable(this);
	return this->y;
}
void ZombieShot::setDirection(int dir){

}
int ZombieShot::getId(){
	return this->id;
}

ZombieShot::~ZombieShot() {
	// TODO Auto-generated destructor stub
}

