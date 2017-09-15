/*
 * BonusKillAll.cpp
 *
 *  Created on: 16/11/2016
 *      Author: usuario
 */

#include "BonusKillAll.h"
#include <sstream>
#include <iostream>

int BonusKillAll::newId = 0;
#define BOX_HEIGHT 10
#define BOX_WIDTH 10
using namespace std;
BonusKillAll::BonusKillAll(int x,int y,int screenPosition,CollisionMap* map,AnimationsRequest* requester):id(newId++){
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->used = false;
	this->setAnimationRequest(requester);
	this->x = x;
	this->y = y+23;
	bonusBox = new CollisionRectangle(x,y,BOX_HEIGHT,BOX_WIDTH,0,0);
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::BONUS_KILL_ALL);
	id.append(str);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(bonusBox);
	this->setCollisionMap(map);
	this->setAnimationID(id);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->type.append(utils::BONUS_KILL_ALL);
	this->screenPosition = screenPosition;
	this->anchoPantalla = utils::SCREEN_WIDTH;

}

std::string BonusKillAll::getType(){
	return this->type;
}

void BonusKillAll::collisioned(Collisionable*){

}

int BonusKillAll::getLeftLimit(){
	return this->x;
}

int BonusKillAll::getRightLimit(){
	return this->x+BOX_WIDTH;
}

bool BonusKillAll::isConnected(){
	return active;
}

void BonusKillAll::activateBonus(){
	this->requester->bonusActivated(this->getAnimationID());
}
bool BonusKillAll::collisionWith(Collisionable* other){
	return other->collisionWith(this);
}
bool BonusKillAll::collisionWith(MainCharacter* other){
	if(this->active){
		this->activateBonus();
		this->active = false;
	}
	return false;
}
bool BonusKillAll::collisionWith(EnemyCharacter* other){
	return false;
}
bool BonusKillAll::collisionWith(Animation* other){
	return false;
}

int BonusKillAll::getDisplacement(){
	return 0;
}
std::string BonusKillAll::getFrame(){
	return "0";
}
int BonusKillAll::getXPos(Parallax* gameBackground){
	if(used){
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	return screenPosition;
}
int BonusKillAll::getYPos(){
	return this->y;
}
BonusKillAll::~BonusKillAll() {
	// TODO Auto-generated destructor stub
}

