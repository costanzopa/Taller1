/*
 * EnemyCharacters.cpp
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#include "EnemyCharacter.h"
#include <cstdlib>
#include <iostream>
EnemyCharacter::EnemyCharacter(float scale,std::string ID,int vel,int dmg,list<MainCharacter*>* characters,CharactersRequest* requestHandler,AnimationsRequest* animsRequest,CollisionMap* map) {
	x=y=screenPosition=0;
	this->scale = scale;
	this->setAnimationsRequest(animsRequest);
	this->setIntroductionMessage(utils::NEW_ENEMY);
	this->setExistingMessage(utils::EXISTING_ENEMY);
	this->setCharactersRequest(requestHandler);
	this->setCollisionMap(map);
	this->alive = true;
	this->onScreen=true;
	this->dead= false;

	this->setActionsList();
	this->setCharacterID(ID);
	this->velocidad = vel;
	this->healthPoints = 30;
	this->damage = dmg;
	appearedOnScreen = false;
	frame_selector =0;
	anchoPantalla = utils::SCREEN_WIDTH;
	this->charsInGame = characters;
	this->setTarget();
	targetPosition = charTarget->getScreenPosition();

}
void EnemyCharacter::setTarget(){
	int index = rand() % this->charsInGame->size();
	list<MainCharacter*>::iterator iter1;
	iter1 = this->charsInGame->begin();
	for(int i=0;i<index;i++)
		iter1++;
	this->charTarget = (*iter1);

}
void EnemyCharacter::killAll(){
	if(appearedOnScreen)
		this->die();
}
void EnemyCharacter::die(){
	this->alive = false;
}
bool EnemyCharacter::collisionWith(Collisionable* collided){
	if(!alive)
		return false;
	return collided->collisionWith(this);
}
bool EnemyCharacter::collisionWith(MainCharacter* collided){
	if(!alive)
			return false;
	return true;
}
bool EnemyCharacter::collisionWith(EnemyCharacter* collided){
	return false;
}
bool EnemyCharacter::collisionWith(Animation* collided){
	if(!alive)
			return false;
	return collided->collisionWith(this);
}
void EnemyCharacter::collisioned(Collisionable*){

}
int EnemyCharacter::getDisplacement(){
	return 0;
}
int EnemyCharacter::getLeftLimit(){
	return this->x;
}
int EnemyCharacter::getRightLimit(){
	return this->x+50;
}
bool EnemyCharacter::isConnected(){
	return true;
}
bool EnemyCharacter::hasID(std::string& ID){
	if (this->getCharacterID().compare(ID)==0)
		return true;
	return false;
}
std::string EnemyCharacter::getInfo(){
	return "";
}
std::string EnemyCharacter::getFrame(){
	if(!alive){
		this->dead=true;
		this->setExistingMessage(utils::DYING_ENEMY);
	}
	return "0";
}
Animation* EnemyCharacter::getNewAction(){
	return NULL;
}

int EnemyCharacter::getXPos(std::Parallax* map){
	if(!alive){
		this->setCharacterScreenPosition(map->position);
		return screenPosition;
	}
	if((map->position + anchoPantalla/2) > this->x)
		appearedOnScreen = true;
	this->nextMove();
	this->setCharacterScreenPosition(map->position);
	return screenPosition;

}
void EnemyCharacter::setCharacterPosition(int X,int Y){
	//cout<<"Setting pos	"<<X<<"		"<<Y<<endl;
	this->x = X;
	this->y =Y;
	this->collisionMap->resetCollisionable(this);
}
void EnemyCharacter::setCharacterScreenPosition(int mapPosition){
	int medioAncho = anchoPantalla/2;
	//if(mapPosition>medioAncho)
		this->screenPosition = this->x - mapPosition + medioAncho;
}
int EnemyCharacter::getYPos(){
	if(!alive)
			return this->y;
	return this->y;
}
EnemyCharacter::~EnemyCharacter() {
	// TODO Auto-generated destructor stub
}

