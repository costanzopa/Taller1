/*
 * GroundFloor.h
 *
 *  Created on: 20/11/2016
 *      Author: usuario
 */

#ifndef GROUNDFLOOR_H_
#define GROUNDFLOOR_H_

#include "Collisionable.h"

class GroundFloor: public Collisionable {
public:
	int x;
	int y;
	int height;
	int width;
	CollisionRectangle* floor;
	GroundFloor(int x,int y,int width, int height,CollisionMap* map);
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	virtual void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual ~GroundFloor();
};

#endif /* GROUNDFLOOR_H_ */
