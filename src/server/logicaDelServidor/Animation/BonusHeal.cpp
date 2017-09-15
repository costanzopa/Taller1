/*
 * BonusHeal.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "BonusHeal.h"
#include <sstream>
#include <iostream>

int BonusHeal::newId = 0;
#define BOX_HEIGHT 10
#define BOX_WIDTH 10
namespace std {

BonusHeal::BonusHeal(int x,int y,int screenPosition,CollisionMap* map,AnimationsRequest* requester):id(newId++){
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
	id.append(utils::BONUS_HEAL);
	id.append(str);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(bonusBox);
	this->setCollisionMap(map);
	this->setAnimationID(id);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->type.append(utils::BONUS_HEAL);
	this->screenPosition = screenPosition;
	this->anchoPantalla = utils::SCREEN_WIDTH;

}

std::string BonusHeal::getType(){
	return this->type;
}

void BonusHeal::collisioned(Collisionable*){

}

int BonusHeal::getLeftLimit(){
	return this->x;
}

int BonusHeal::getRightLimit(){
	return this->x+BOX_WIDTH;
}

bool BonusHeal::isConnected(){
	return active;
}

void BonusHeal::activateBonus(){
	this->requester->bonusActivated(this->getAnimationID());
}
bool BonusHeal::collisionWith(Collisionable* other){
	return other->collisionWith(this);
}
bool BonusHeal::collisionWith(MainCharacter* other){
	if(this->active){
		this->activateBonus();
		this->active = false;
	}
	return false;
}
bool BonusHeal::collisionWith(EnemyCharacter* other){
	return false;
}
bool BonusHeal::collisionWith(Animation* other){
	return false;
}

int BonusHeal::getDisplacement(){
	return 0;
}
std::string BonusHeal::getFrame(){
	return "0";
}
int BonusHeal::getXPos(Parallax* gameBackground){
	if(used){
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	return screenPosition;
}
int BonusHeal::getYPos(){
	return this->y;
}
BonusHeal::~BonusHeal() {
	// TODO Auto-generated destructor stub
}


} /* namespace std */
