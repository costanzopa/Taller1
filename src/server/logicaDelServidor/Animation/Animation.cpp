/*
 * Animation.cpp
 *
 *  Created on: 1/11/2016
 *      Author: usuario
 */

#include "Animation.h"
#include <iostream>
using namespace std;
Animation::Animation() {
	// TODO Auto-generated constructor stub

}
std::string& Animation::getAnimationID(){
	return animationID;
}
std::string& Animation::getAnimationImage(){
	return imagePath;
}
std::string& Animation::getIntroductionMessage(){
	return introductionMessage;
}
std::string& Animation::getExistingMessage(){
	if(this->dissapeared){
		this->collisionMap->removeCollisionable(this);
		this->collisionMap = NULL;
		this->requester->addNewRequest(this->animationID);
		this->onScreen = false;
	}
	return this->existingMessage;
}
void Animation::destroyAnimation(){
	if(this->collisionMap)
		this->collisionMap->removeCollisionable(this);
}
void Animation::setExistingMessage(const std::string existing){
	this->existingMessage = existing;
}
void Animation::setAnimationRequest(AnimationsRequest* requests){
	this->requester = requests;
}
void Animation::setIntroductionMessage(const std::string newMessage){
	this->introductionMessage.append(newMessage);
}
void Animation::setAnimationImage(const std::string& imagePath){
	this->imagePath = imagePath;
}
void Animation::setAnimationID(const std::string& animationIDd){
	this->animationID = animationIDd;
}
Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

