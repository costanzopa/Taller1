/*
 * CharactersInGame.cpp
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#include "CharactersInGame.h"
#include <iostream>
#include <sstream>

using namespace std;

CharactersInGame::CharactersInGame() {
	pthread_mutex_init(&mutex,NULL);
	charsPlaying = new list<Character*>();
}
void CharactersInGame::setBackground(Parallax* background){
	gameBackground = background;
}
void CharactersInGame::addNewPlayer(Character* newCharacter){
	charsPlaying->push_back(newCharacter);
}
void CharactersInGame::removePlayer(std::string ID){
	list<Character*>:: iterator iter1;
	iter1 = charsPlaying->begin();
	while(iter1 != charsPlaying->end()){
		if((*iter1)->getCharacterID().compare(ID) == 0){
			this->lock();
			if(iter1 == broadcastIter)
				broadcastIter++;
			charsPlaying->erase(iter1);
			this->unlock();
			break;
		}
		iter1++;
	}
}
Character* CharactersInGame::getCharacter(string ID){
	list<Character*>:: iterator iter1;
	iter1 = charsPlaying->begin();
	while(iter1 != charsPlaying->end()){
		if((*iter1)->getCharacterID().compare(ID) == 0){
			Character* actioner = *iter1;
			return actioner;
		}
		iter1++;
	}
	return NULL;
}
Node* CharactersInGame::getCharacterSettings(User* from,User* to){
	this->lock();
	bool connected = (*broadcastIter)->isConnected();
	string img = (*broadcastIter)->getCharacterImage();
	string msj_image;
	msj_image.append((*broadcastIter)->getIntroductionMessage());
	msj_image.append("|");
	msj_image.append((*broadcastIter)->getCharacterID());
	msj_image.append("|");
	msj_image.append(img);
	msj_image.append("|");
	if(connected){
		msj_image.append(utils::CONNECTED);
	}else{
		msj_image.append(utils::DISCONNECTED);
	}
	this->unlock();
	return new Node(from,to,msj_image);

}
void CharactersInGame::initBroadCast(){
	this->lock();
	broadcastIter = charsPlaying->begin();
	this->unlock();
}

Node* CharactersInGame::getCharacterStatus(User* from,User* to){
	this->lock();
	bool connected = (*broadcastIter)->isConnected();
	std::string msj;
	msj.append((*broadcastIter)->getExistingMessage());
	msj.append("|");
	msj.append((*broadcastIter)->getCharacterID());
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
	this->unlock();
	return new Node(from,to,msj);
}
string CharactersInGame::getCharacterStatus(){
	this->lock();
	std::string msj;
	int x_pos = (*broadcastIter)->getXPos(this->gameBackground);
	if((*broadcastIter)->appearsOnScreen()){
	bool connected = (*broadcastIter)->isConnected();
	msj.append((*broadcastIter)->getExistingMessage());
	msj.append("|");
	msj.append((*broadcastIter)->getCharacterID());
	msj.append("|");
	std::string x;
	std::stringstream out;
	out << x_pos;
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
	}else{
		msj.append(utils::NO_NEW_ACTION);
	}
	broadcastIter ++;
	this->unlock();
	return msj;
}
std::string CharactersInGame::getCharacterInfo(){
	this->lock();
	std::string msj;
	msj.append(utils::NEW_INFO);
	msj.append("|");
	msj.append((*broadcastIter)->getCharacterID());
	msj.append("|");
	std::string x;
	std::stringstream out;
	//TODO chequear si no es MainCharacter antes de pedir puntos si anda lento
	out << (*broadcastIter)->getInfo() << CharacterMap::getTotalPoints((*broadcastIter)->getCharacterID()) << " 1 " << (*broadcastIter)->healthPoints;
	x = out.str();
	msj.append(x);
	broadcastIter ++;
	this->unlock();
	return msj;
}
std::string CharactersInGame::getCharacterLevelInfo(){
	this->lock();
	std::string msj;
	if((*broadcastIter)->existingMessage.compare(utils::EXISTING_CHARACTER) != 0)
		return msj;
	msj.append(utils::LEVEL_INFO);
	msj.append("|");
	msj.append((*broadcastIter)->getCharacterID());
	msj.append("|");
	std::string x;
	std::stringstream out;
	bool gano = CharacterMap::teamWon((*broadcastIter)->getCharacterID());
	out << CharacterMap::getPoints((*broadcastIter)->getCharacterID()) << "|" << gano;
	x = out.str();
	msj.append(x);
	broadcastIter ++;
	this->unlock();
	return msj;
}
void CharactersInGame::nohacernada(){

}

std::string CharactersInGame::getCharacterNewAction(){
	this->lock();
	std::string msj;
	if((*broadcastIter)->onScreen){
	bool connected = (*broadcastIter)->isConnected();
	msj.append((*broadcastIter)->getExistingMessage());
	msj.append("|");
	msj.append((*broadcastIter)->getCharacterID());
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
	std::string frame;
	std::stringstream out3;
	out3 << (*broadcastIter)->getFrame();
	frame = out3.str();
	msj.append("|");
	msj.append(frame);
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
bool CharactersInGame::finished(){
	if(broadcastIter == charsPlaying->end()){
		return true;
	}
	return false;

}
CharactersInGame::~CharactersInGame() {
	// TODO Auto-generated destructor stub
}

