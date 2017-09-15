/*
 * CollisionElipse.h
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONELIPSE_H_
#define COLLISIONELIPSE_H_
#include <pthread.h>
#include "CollisionFigure.h"
#include "CollisionRectangle.h"
class CollisionElipse: public CollisionFigure {
public:
	int xOffset;
	int yOffset;
	int x_center;
	int y_center;
	int radius;
	pthread_mutex_t mlock;
	CollisionElipse(int,int,int,int,int);
	virtual void setOffset(int,int);
	virtual void setPosition(int,int);
	virtual bool collisions(CollisionFigure*);
	virtual bool collisions(CollisionRectangle*);
	virtual bool collisions(CollisionElipse*);
	virtual ~CollisionElipse();
private:
	void lock(){ pthread_mutex_lock(&mlock);}
	void unlock(){ pthread_mutex_unlock(&mlock);}
};

#endif /* COLLISIONECLIPSE_H_ */
