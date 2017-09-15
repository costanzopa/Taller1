/*
 * GameController.h
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_
#include <list>
#include <string>
#include <unistd.h>
#include "../../../common/threads/Thread.h"
#include "../../../estructurasDeDatos/CharactersInGame.h"
#include "../../../estructurasDeDatos/AnimationsInGame.h"
#include "../Animation/Animation.h"
#include "../Character/Character.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"
class GameManager;
using namespace std;
class GameController: public threads::Thread {
public:
	CharactersRequest* charRequests;
	AnimationsRequest* animsRequests;
	CharactersInGame* characters;
	AnimationsInGame* animations;
	list<EnemyCharacter*>* enemyList;
	GameManager* gameManager;
	list<MainCharacter*>* charList;
	int playersAlive;
	GameController(CharactersInGame*,CharactersRequest*,AnimationsInGame*,AnimationsRequest*);
	void attendPushAnimationRequest();
	void setGameManager(GameManager*);
	void setCharactersList(list<MainCharacter*>*);
	void setEnemiesList(list<EnemyCharacter*>*);
	void checkGameFinished(std::string);
	void gameOver();
	void levelWon();
	void activateBonus();
	void attendPopCharacterRequest();
	void attendPopAnimationRequest();
	void addEnemy();
	virtual void stop();
	virtual ~GameController();
private:
	virtual void* process();
};

#endif /* GAMECONTROLLER_H_ */
