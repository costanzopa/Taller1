/*
 * CharactersInGame.h
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#ifndef CHARACTERSINGAME_H_
#define CHARACTERSINGAME_H_
#include <pthread.h>
#include <iostream>
#include "../server/logicaDelServidor/Character/Character.h"
#include "../server/logicaDelServidor/GameRelated/CharacterMap.h"
#include "AnimationsInGame.h"
#include "list"
#include <string>
#include "Node.h"

using namespace std;
class CharactersInGame {
public:

	CharactersInGame();
	void setBackground(Parallax*);
	void addNewPlayer(Character*);
	void removePlayer(std::string);
	void initBroadCast();
	Character* getCharacter(std::string);
	Node* getCharacterStatus(User*,User*);
	Node* getCharacterSettings(User*,User*);
	string getCharacterNewAction();
	string getCharacterInfo();
	string getCharacterLevelInfo();
	string getCharacterStatus();
	void nohacernada();
	bool finished();
	virtual ~CharactersInGame();
	list<Character*>* charsPlaying;
	pthread_mutex_t mutex;
	list<Character*>:: iterator broadcastIter;
	Parallax* gameBackground;
private:
		void lock(){ pthread_mutex_lock(&mutex);}
		void unlock(){ pthread_mutex_unlock(&mutex);}
};

#endif /* CHARACTERSINGAME_H_ */
