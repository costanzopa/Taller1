/*
 * CollisionRectangule.h
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONRECTANGLE_H_
#define COLLISIONRECTANGLE_H_
#include <pthread.h>
#include "CollisionFigure.h"
#include "CollisionElipse.h"
class CollisionRectangle: public CollisionFigure {
public:
	int xOffset;
	int yOffset;
	int x;
	int y;
	int height;
	int width;
	pthread_mutex_t mlock;
	CollisionRectangle(int,int,int,int,int,int);
	virtual void setOffset(int,int);
	virtual void setPosition(int,int);
	virtual bool collisions(CollisionFigure*);
	virtual bool collisions(CollisionRectangle*);
	virtual bool collisions(CollisionElipse*);
	virtual ~CollisionRectangle();
private:
	void lock(){ pthread_mutex_lock(&mlock);}
	void unlock(){ pthread_mutex_unlock(&mlock);}
};

#endif /* COLLISIONRECTANGLE_H_ */
