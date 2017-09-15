/*
 * CharactersRequest.h
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#ifndef CHARACTERSREQUEST_H_
#define CHARACTERSREQUEST_H_
#include <list>
#include <string>
#include <iostream>
class EnemyCharacter;
using namespace std;
class CharactersRequest {
public:
	CharactersRequest();
	std::list<std::string>* charsRequests;
	std::list<std::string>* dyingCharsRequests;
	std::list<std::string>::iterator iter;
	std::list<EnemyCharacter*>::iterator enemyIterator;
	void addNewRequest(std::string);
	void addNewDyingRequest(std::string);
	std::string getCharactersRequest();
	std::string getDyingRequest();
	bool hasCharactersRequests();
	bool hasDyingCharactersRequests();
	bool hasEnemiesRequests();
	virtual ~CharactersRequest();
	std::list<EnemyCharacter*>* enemiesRequest;
	void addEnemy(EnemyCharacter* enemy);
	EnemyCharacter* getEnemyRequest();

};

#endif /* CHARACTERSREQUEST_H_ */
