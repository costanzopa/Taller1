/*
 * Character.cpp
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */
#include "Character.h"

Character::Character(){

}
void Character::setCharactersRequest(CharactersRequest* requestHandler){
	this->requestHandler = requestHandler;
}
Animation* Character::getNewAction(){
	if(!playerActions->empty()){
		iter = playerActions->begin();
		Animation* newAction = *iter;
		playerActions->erase(iter);
		return newAction;
	}
	//cout<<"I give them shit"<<endl;
	return NULL;
}
std::string& Character::getIntroductionMessage(){
	return introductionMessage;
}
std::string& Character::getExistingMessage(){
	if(this->dead){
		this->onScreen = false;
		this->collisionMap->removeCollisionable(this);
		this->requestHandler->addNewDyingRequest(this->characterID);
}
	return existingMessage;
}
void Character::recieveDamage(int damage){
	if(this->characterID.compare("luis")==0 || !alive)
		return;
	this->healthPoints -= damage;
	if(this->healthPoints<=0){
		this->healthPoints = 0;
		//cout<<"Hundiste mi acorazado"<<endl;
		this->die();
	}
}
void Character::setExistingMessage(const std::string existing){
	this->existingMessage = existing;
}
void Character::setIntroductionMessage(const std::string newMessage){
	this->introductionMessage.append(newMessage);
}
void Character::setActionsList(){
	playerActions = new list<Animation*>();
}
void Character::setAnimationsRequest(AnimationsRequest* requesHandler){
	this->animsRequestHandler = requesHandler;
}
Character::~Character(){

}
std::string& Character::getCharacterID() {
	return this->characterID;
}

std::string& Character::getCharacterImage() {
	return this->imagePath;
}
std::string Character::getInfo(){
	return "";
}
void Character::setCharacterID(const std::string& characterID) {
	this->characterID = characterID;
}

void Character::setCharacterImage(const std::string& imagePath) {
	this->imagePath = imagePath;
}


