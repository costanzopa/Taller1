/*
 * CollisionRectangule.cpp
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#include "CollisionRectangle.h"
#include <iostream>
using namespace std;
CollisionRectangle::CollisionRectangle(int x,int y,int width,int height,int xOffset,int yOffset) {
	pthread_mutex_init(&mlock,NULL);
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->x = x+xOffset;
	this->y = y+yOffset;
	this->height = height;
	this->width = width;

}
void CollisionRectangle::setOffset(int x,int y){
	this->lock();
	this->xOffset = x;
	this->yOffset = y;
	this->unlock();
}
void CollisionRectangle::setPosition(int x,int y){
	this->lock();
	this->x = x+xOffset;
	this->y = y+yOffset;
	this->unlock();
}
bool CollisionRectangle::collisions(CollisionFigure* collisioned){
	return collisioned->collisions(this);
}
bool CollisionRectangle::collisions(CollisionRectangle* other){

	int x1_end = this->x + this->width;
	int x1_begin = this->x;
	int x2_begin = other->x;
	int x2_end = other->x + other->width;

	if(((x1_end < x2_begin)||(x1_begin > x2_end)))
		return false;
	int y1_end = this->y + this->height;
	int y1_begin = this->y;
	int y2_begin = other->y;
	int y2_end = other->y + other->height;
	if((y1_begin > y2_end && y1_begin > y2_begin)||(y1_end < y2_begin && y1_end < y2_end))
		return false;
	return true;
}

bool CollisionRectangle::collisions(CollisionElipse* other){
	return other->collisions(this);

}

CollisionRectangle::~CollisionRectangle() {
	// TODO Auto-generated destructor stub
}

