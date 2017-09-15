/*
 * AnimationsInGame.cpp
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#include "AnimationsInGame.h"
#include "../server/logicaDelServidor/Animation/Animation.h"
#include <sstream>

AnimationsInGame::AnimationsInGame(){
	pthread_mutex_init(&mutex,NULL);
	activeAnimations = new list<Animation*>();
	newAnimations = new list<Animation*>();
}
void AnimationsInGame::setBackground(Parallax* background){
	gameBackground = background;
}
Animation* AnimationsInGame::getAnimation(std::string ID){
	list<Animation*>::iterator iter1;
	iter1 = activeAnimations->begin();
	while(iter1 != activeAnimations->end()){
		if((*iter1)->getAnimationID().compare(ID)==0)
			return (*iter1);
		iter1++;
	}
}
void AnimationsInGame::addNewAnimation(Animation* newAnimation){
	//cout<<"We add a new animation"<<endl;
	newAnimations->push_back(newAnimation);
}
void AnimationsInGame::resetAnimations(){
	list<Animation*>:: iterator iter1;
	iter1 = activeAnimations->begin();
	while(iter1 != activeAnimations->end()){
		(*iter1)->destroyAnimation();
		Animation* destroying = *iter1;
		activeAnimations->erase(iter1);
		delete destroying;
		iter1 = activeAnimations->begin();
	}
}
void AnimationsInGame::removeAnimation(std::string ID){
	list<Animation*>:: iterator iter1;
	iter1 = activeAnimations->begin();
	//cout<<"Vamos a sacar la animacion"<<endl;
	while(iter1 != activeAnimations->end()){;
		if((*iter1)->getAnimationID().compare(ID) == 0){
			this->lock();
			if(iter1 == broadcastIter)
				broadcastIter++;
			Animation* animationDelete = (*iter1);
			activeAnimations->erase(iter1);
			this->unlock();
			delete animationDelete;
			break;
		}
		iter1++;
	}
}

void AnimationsInGame::initBroadCast(){
	this->lock();
	broadcastIter = activeAnimations->begin();
	this->unlock();
}
std::string AnimationsInGame::getNewAnimationSettings(){
	//cout<<"We ask new animations"<<endl;
	newAnimIter =newAnimations->begin();
	bool connected = true;
	string msj_image;
	msj_image.append((*newAnimIter)->getIntroductionMessage());
	msj_image.append("|");
	msj_image.append((*newAnimIter)->getType());
	msj_image.append("|");
	msj_image.append((*newAnimIter)->getAnimationID());
	msj_image.append("|");
	std::string x;
	std::stringstream out;
	out << (*newAnimIter)->getXPos(this->gameBackground);
	x = out.str();
	msj_image.append(x);
	msj_image.append(":");
	std::string y;
	std::stringstream out2;
	out2 << (*newAnimIter)->getYPos();
	y = out2.str();
	msj_image.append(y);
	msj_image.append("|");
	msj_image.append((*newAnimIter)->getFrame());
	msj_image.append("|");
	if(connected){
		msj_image.append(utils::CONNECTED);
	}else{
		msj_image.append(utils::DISCONNECTED);
	}
	activeAnimations->push_back(*newAnimIter);
	newAnimations->erase(newAnimIter);
	return msj_image;

}
std::string AnimationsInGame::getAnimationsMessages(){
	if(!newAnimations->empty()){
			string msj;
			return this->getNewAnimationSettings();
	}
	this->lock();
	std::string msj;
	if(broadcastIter == activeAnimations->end() || (*broadcastIter)->onScreen){
	bool connected = (*broadcastIter)->isConnected();
	msj.append((*broadcastIter)->getExistingMessage());
	msj.append("|");
	msj.append((*broadcastIter)->getType());
	msj.append("|");
	msj.append((*broadcastIter)->getAnimationID());
	msj.append("|");
	std::string x;
	std::stringstream out;
	out << (*broadcastIter)->getXPos(this->gameBackground);
	x = out.str();
	msj.append(x);
	msj.append(":");
	std::string y;
	std::stringstream out2;
	out2 << (*broadcastIter)->getYPos();
	y = out2.str();
	msj.append(y);
	msj.append("|");
	msj.append((*broadcastIter)->getFrame());
	msj.append("|");
	if(connected){
			msj.append(utils::CONNECTED);
		}else{
			msj.append(utils::DISCONNECTED);
		}
	broadcastIter ++;
	}else{
		msj.append(utils::NO_NEW_ACTION);
		broadcastIter++;
	}
	this->unlock();
	return msj;
}
bool AnimationsInGame::finished(){
	if(!newAnimations->empty())
		return false;
	if(broadcastIter == activeAnimations->end()){
		return true;
	}

	return false;

}
AnimationsInGame::~AnimationsInGame() {
	// TODO Auto-generated destructor stub
}

