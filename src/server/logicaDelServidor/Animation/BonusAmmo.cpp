/*
 * BonusAmmo.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "BonusAmmo.h"
#include <sstream>
#include <iostream>

#define BOX_HEIGHT 10
#define BOX_WIDTH 10
namespace std {

BonusAmmo::BonusAmmo(int x,int y,int screenPosition,CollisionMap* map,AnimationsRequest* requester){
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->used = false;
	this->setAnimationRequest(requester);
	this->x = x;
	this->y = y+18;
	bonusBox = new CollisionRectangle(x,y,BOX_HEIGHT,BOX_WIDTH,0,0);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(bonusBox);
	this->setCollisionMap(map);
	this->active = true;
	this->onScreen = true;
	this->dissapeared = false;
	this->screenPosition = screenPosition;
	this->anchoPantalla = utils::SCREEN_WIDTH;

}

std::string BonusAmmo::getType(){
	return this->type;
}

void BonusAmmo::collisioned(Collisionable*){

}

int BonusAmmo::getLeftLimit(){
	return this->x;
}

int BonusAmmo::getRightLimit(){
	return this->x+BOX_WIDTH;
}

bool BonusAmmo::isConnected(){
	return active;
}

void BonusAmmo::activateBonus(){
	this->requester->bonusActivated(this->getAnimationID());
}
bool BonusAmmo::collisionWith(Collisionable* other){
	return other->collisionWith(this);
}
bool BonusAmmo::collisionWith(MainCharacter* other){
	if(this->active){
		this->activateBonus();
		this->active = false;
	}
	return false;
}
bool BonusAmmo::collisionWith(EnemyCharacter* other){
	return false;
}
bool BonusAmmo::collisionWith(Animation* other){
	return false;
}

int BonusAmmo::getDisplacement(){
	return 0;
}
std::string BonusAmmo::getFrame(){
	return "0";
}
int BonusAmmo::getXPos(Parallax* gameBackground){
	if(used){
		this->setExistingMessage(utils::DISSAPEAR_ANIMATION);
	}
	int mapPosition = gameBackground->position;
	int medioAncho = anchoPantalla/2;
	this->screenPosition = this->x - mapPosition + medioAncho;
	this->collisionMap->moveAttemptCollisionable(this);
	return screenPosition;
}
int BonusAmmo::getYPos(){
	return this->y;
}
BonusAmmo::~BonusAmmo() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
