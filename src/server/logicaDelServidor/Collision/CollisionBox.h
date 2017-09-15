/*
 * CollisionBox.h
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONBOX_H_
#define COLLISIONBOX_H_
#include "CollisionFigure.h"
#include <list>

using namespace std;
class CollisionBox {
public:
	list<CollisionFigure*>::iterator iter;
	list<CollisionFigure*>* hitBox;
	CollisionBox();
	bool collisions(CollisionBox*);
	void addNewHitbox(CollisionFigure*);
	void moveCollisionBox(int,int);
	virtual ~CollisionBox();
};

#endif /* COLLISIONBOX_H_ */
