/*
 * CollisionFigure.h
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONFIGURE_H_
#define COLLISIONFIGURE_H_
#include <cstdlib>
class CollisionElipse;
class CollisionRectangle;
class CollisionFigure {
public:
	CollisionFigure();
	virtual void setOffset(int,int)=0;
	virtual void setPosition(int,int)=0;
	virtual bool collisions(CollisionFigure*)= 0;
	virtual bool collisions(CollisionRectangle*)=0;
	virtual bool collisions(CollisionElipse*)=0;
	virtual ~CollisionFigure();
};

#endif /* COLLISIONFIGURE_H_ */
