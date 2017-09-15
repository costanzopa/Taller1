/*
 * UfoEnemy.h
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#ifndef UFOENEMY_H_
#define UFOENEMY_H_

#include "EnemyCharacter.h"
#include <list>

using namespace std;


class UfoEnemy: public EnemyCharacter {
public:
	UfoEnemy(float,list<EnemyCharacter*>* ufoSpawns, std::string,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	virtual void nextMove();
	int headRadio;
	int side1Radio;
	int side2Radio;
	int bodyWidth;
	int bodyHeight;
	virtual std::string getFrame();
	CollisionElipse* side1;
	CollisionElipse* side2;
	CollisionElipse* head;
	CollisionRectangle* body;
	virtual ~UfoEnemy();
	bool spawning;
	bool firstTime;
	bool goLeft;
	int frame;
	int spawnFrame;
	int initialPosition;
	void spawnZombie();
	int counter;
	list<EnemyCharacter*>* spawns;
	std::list<EnemyCharacter*>::iterator it;
};

#endif /* UFOENEMY_H_ */
