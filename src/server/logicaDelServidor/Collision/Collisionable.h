/*
 * Collisionable.h
 *
 *  Created on: 3/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONABLE_H_
#define COLLISIONABLE_H_
#include "CollisionMap.h"
#include "CollisionBox.h"
#include "CollisionElipse.h"
#include "CollisionRectangle.h"
class MainCharacter;
class EnemyCharacter;
class Animation;
class Collisionable {
public:
	Collisionable();
	virtual ~Collisionable();
	void setCollisionMap(CollisionMap*);
	virtual bool collisionWith(Collisionable*) =0;
	virtual bool collisionWith(MainCharacter*) =0;
	virtual bool collisionWith(EnemyCharacter*)=0;
	virtual bool collisionWith(Animation*) =0;
	void setCollisionBox();
	bool collisions(Collisionable*);
	virtual void collisioned(Collisionable*)=0;
	virtual int getDisplacement()= 0;
	virtual int getLeftLimit()= 0;
	virtual int getRightLimit() =0;
	CollisionBox* hitBox;
	CollisionMap* collisionMap;

};

#endif /* COLLISIONABLE_H_ */
