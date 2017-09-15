/*
 * RangeEnemy.h
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#ifndef RANGEENEMY_H_
#define RANGEENEMY_H_
#include "EnemyCharacter.h"
#include "../Animation/ZombieShot.h"
 #include "stdlib.h"
using namespace std;

class RangeEnemy: public EnemyCharacter{
enum Direction {right , left};
public:
	int range;
	int longBodyHeight;
	int feetHeight;
	int longBodyWidth;
	int feetWidth;
	CollisionRectangle* longBody;
	CollisionRectangle* feet;
	int sequence_select;
	int sequence_offset;
	bool attacking;
	bool thinking;
	int movingFrames;
	int thinkingFrames;
	int attackingFrames;
	int dyingFrames;
	Direction currDir;
	std::vector<int>* shot_table;
	int shotCapability;
	void shoot();
	RangeEnemy(float,std::string,int,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	int getFrameInt();
	virtual std::string getFrame();
	virtual void die();
	void aSetShotTable();
	virtual void nextMove();
	void selectCurrentSequence();
	virtual ~RangeEnemy();
};

#endif /* RANGEENEMY_H_ */
