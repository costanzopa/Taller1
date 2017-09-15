/*
 * CharactersRequest.cpp
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#include "CharactersRequest.h"
#include "EnemyCharacter.h"


using namespace std;
CharactersRequest::CharactersRequest() {
	this->charsRequests = new list<std::string>();
	this->dyingCharsRequests = new list<std::string>();
	this->enemiesRequest = new list<EnemyCharacter*>();
}
void CharactersRequest::addNewRequest(std::string request){
	this->charsRequests->push_back(request);
}
void CharactersRequest::addNewDyingRequest(std::string request){
	this->dyingCharsRequests->push_back(request);
}
std::string CharactersRequest::getCharactersRequest(){
	iter = this->charsRequests->begin();
	std::string request = *iter;
	this->charsRequests->erase(iter);
	return request;
}
std::string CharactersRequest::getDyingRequest(){
	iter = this->dyingCharsRequests->begin();
	std::string request = *iter;
	this->dyingCharsRequests->erase(iter);
	return request;
}
EnemyCharacter* CharactersRequest::getEnemyRequest(){
	//cout << "1" << endl;
	enemyIterator = this->enemiesRequest->begin();
	//cout << "2" << endl;
	EnemyCharacter* request = *enemyIterator;
	//cout << "3" << endl;
	this->enemiesRequest->erase(enemyIterator);
	//cout << "4" << endl;
	return request;
}
bool CharactersRequest::hasCharactersRequests(){
	return this->charsRequests->empty();
}
bool CharactersRequest::hasDyingCharactersRequests(){
	return this->dyingCharsRequests->empty();
}
bool CharactersRequest::hasEnemiesRequests(){
	return this->enemiesRequest->empty();
}
void CharactersRequest::addEnemy(EnemyCharacter* enemy) {
	this->enemiesRequest->push_back(enemy);
}

CharactersRequest::~CharactersRequest() {
	// TODO Auto-generated destructor stub
}

