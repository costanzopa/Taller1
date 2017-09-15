/*
 * GameController.cpp
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#include "GameController.h"
#include "GameManager.h"
#include "../Animation/Bonus.h"
using namespace std;
GameController::GameController(CharactersInGame* characters,CharactersRequest* charsRequests,AnimationsInGame* animations, AnimationsRequest* animsRequest){
	this->charRequests = charsRequests;
	this->animsRequests = animsRequest;
	this->animations = animations;
	this->characters = characters;
	this->charList = NULL;
	this->enemyList = NULL;

}
void GameController::setGameManager(GameManager* gameManager){
	this->gameManager = gameManager;
}
void GameController::attendPushAnimationRequest(){
	std::string shooterID = this->charRequests->getCharactersRequest();
	Character* shootingCharacter = this->characters->getCharacter(shooterID);
	Animation* animation = shootingCharacter->getNewAction();
	this->animations->addNewAnimation(animation);
}
void GameController::setCharactersList(list<MainCharacter*>* list){
	playersAlive = list->size();
	//cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<playersAlive<<endl;
	if(!this->charList)
		delete this->charList;
	this->charList = list;
}
void GameController::setEnemiesList(list<EnemyCharacter*>* list){
	if(!this->enemyList)
			delete this->enemyList;
		this->enemyList = list;
}
void GameController::attendPopCharacterRequest(){
	std::string charID = this->charRequests->getDyingRequest();
	this->characters->removePlayer(charID);
	this->checkGameFinished(charID);
}
void GameController::gameOver(){
	this->gameManager->gameOver();
}
void GameController::levelWon(){
	this->gameManager->nextLevel();
	this->animsRequests->empty();
}
void GameController::checkGameFinished(std::string id){
	//cout<<id<<endl;
	//cout<<enemyList->size()<<endl;
	list<EnemyCharacter*>::iterator iter;
	bool found = false;
	iter = enemyList->begin();
	while(iter != enemyList->end()){
		if((*iter)->getCharacterID().compare(id)==0){
			EnemyCharacter* enemy = (*iter);
			enemyList->erase(iter);
			found = true;
			delete enemy;
			break;
		}
		iter ++;
	}
	if(enemyList->empty()){
		this->levelWon();
	}
	if(found){
		return;
	}
	list<MainCharacter*>::iterator iter1;
	iter1 = charList->begin();
	while(iter1 != charList->end()){
		if((*iter1)->getCharacterID().compare(id)==0){
			//charList->erase(iter1);
			playersAlive--;
			found = true;
			break;
		}
		//cout << "Ahora solo quedan: "<<  playersAlive << endl;
		iter1 ++;
	}
	if(!playersAlive){
		this->gameOver();
	}
}
void GameController::activateBonus(){
	//cout<<"Activating bonus"<<endl;
	std::string bonusID = this->animsRequests->getBonusID();
	Animation* bonus = this->animations->getAnimation(bonusID);
	std::string type = bonus->getType();
	((Bonus*)bonus)->activateEffect();
	list<EnemyCharacter*>::iterator iter1;
	list<MainCharacter*>::iterator iter2;
	if(type.compare(utils::BONUS_KILL_ALL)==0){
		iter1 = this->enemyList->begin();
		while(iter1!=this->enemyList->end()){
			(*iter1)->killAll();
			iter1++;
		}
	}
	if(type.compare(utils::BONUS_HEAL)==0){
		iter2 = this->charList->begin();
		while(iter2!=this->charList->end()){
			(*iter2)->healAll();
			iter2++;
		}
	}
}
void GameController::attendPopAnimationRequest(){
	std::string animID = this->animsRequests->getRequest();
	this->animations->removeAnimation(animID);
}
void GameController::stop(){
	Thread::stop();
}
void* GameController::process(){
	while(this->isRunning()){
		if(!charRequests->hasCharactersRequests())
			this->attendPushAnimationRequest();
		if(!charRequests->hasDyingCharactersRequests())
			this->attendPopCharacterRequest();
		if(!animsRequests->animationsDissapearingEmpty())
			this->attendPopAnimationRequest();
		if(!animsRequests->bonusActivatedEmpty())
			this->activateBonus();
		if(!charRequests->hasEnemiesRequests())
			this->addEnemy();
		if(enemyList->empty())
		usleep(4000);
	}
	return (void*)NULL;
}

void GameController::addEnemy(){
	//cout<<"We fetch a Enemy"<<endl;
	EnemyCharacter* e = this->charRequests->getEnemyRequest();
	//cout << "5" << endl;
	this->enemyList->push_back(e);
	//cout << "6" << endl;
	this->characters->addNewPlayer(e);
	//cout << "7" << endl;
}

GameController::~GameController() {
	// TODO Auto-generated destructor stub
}

