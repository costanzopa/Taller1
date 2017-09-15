/*
 * MeleeEnemy.h
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#ifndef MELEEENEMY_H_
#define MELEEENEMY_H_

#include "EnemyCharacter.h"

class MeleeEnemy: public EnemyCharacter {
enum Direction {right , left};
public:
	MeleeEnemy(float,std::string,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	virtual void nextMove();
	virtual std::string getFrame();
	virtual ~MeleeEnemy();
private:
	int longBodyHeight;
	int shortBodyHeight;
	int longBodyWidth;
	int shortBodyWidth;
	CollisionRectangle* longBody;
	CollisionRectangle* shortBody;
	int deathFrame;
	int sequence_selector;
	int sequence_offset;
	int movingFrame;
	int attackingFrame;
	bool attacking;
	Direction direction;
	int getFrameInt();
	virtual void startDeathAnimation();
	void selectCurrentSequence();
	void attack();
};

#endif /* MELEEENEMY_H_ */
