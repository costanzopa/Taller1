/*
 * CollisionEclipse.cpp
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#include "CollisionElipse.h"
#include <iostream>
using namespace std;
CollisionElipse::CollisionElipse(int x,int y,int radius,int xOffset,int yOffset) {
	pthread_mutex_init(&mlock,NULL);
	this->xOffset = xOffset;
	this->yOffset =yOffset;
	this->x_center = x+this->yOffset;
	this->y_center = y+this->xOffset;
	this->radius = radius;

}
void CollisionElipse::setOffset(int x,int y){
	this->lock();
	this->xOffset = x;
	this->yOffset = y;
	this->unlock();
}
bool CollisionElipse::collisions(CollisionFigure* collisioned){
	return collisioned->collisions(this);
}
void CollisionElipse::setPosition(int x,int y){
	this->lock();
	this->x_center = x+xOffset;
	this->y_center =y+yOffset;
	this->unlock();
}
bool CollisionElipse::collisions(CollisionRectangle* other){
	int lower_y = other->y + other->height;
	int elipseLowerLim = this->y_center + this->radius;
	int elipseUpperLim = this->y_center - this->radius;
	if(lower_y < elipseUpperLim || other->y > elipseLowerLim){
		return false;
	}
	int rightMost_x = other->x + other->width;
	int elipseRightLim = this->x_center + this->radius;
	int elipseLeftLim = this->x_center - this->radius;
	if(rightMost_x < elipseLeftLim || other->x > elipseRightLim){
		return false;
	}
	int y_dist;
	int x_dist;
	int dist;
	int sqr_radius = this->radius*this->radius;
	if(other->x >= this->x_center){
		//cout<<"Estamos en este caso"<<endl;
		if(lower_y <= this->y_center){
			//El circulo colisiona con la esquina inferior izquierda del cuadrado
			y_dist = abs(lower_y - this->y_center);
			x_dist = abs(other->x - this->x_center);
			dist = y_dist*y_dist + x_dist*x_dist;
			if(sqr_radius<dist)
				return true;
			return false;
		}else if(other->y >= this->y_center){
			//El circulo colisiona con la esquina superior izquierda del cuadrado
			y_dist = abs(other->y - this->y_center);
			x_dist = abs(other->x - this->x_center);
			dist = y_dist*y_dist + x_dist*x_dist;
			if(sqr_radius<dist)
				return true;
			return false;
		}
		return true;
	}if(rightMost_x <= this->x_center){
		if(lower_y <= this->y_center){
			//El circulo colisiona con la esquina inferior derecha del cuadrado
			y_dist = abs(lower_y - this->y_center);
			x_dist = abs(rightMost_x - this->x_center);
			dist = y_dist*y_dist + x_dist*x_dist;
			if(sqr_radius<dist)
				return true;
			return false;
		}else if(other->y >= this->y_center){
			//El circulo colisiona con la esquina superior derecha del cuadrado
			y_dist = abs(other->y - this->y_center);
			x_dist = abs(rightMost_x - this->x_center);
			dist = y_dist*y_dist + x_dist*x_dist;
			if(sqr_radius<dist)
				return true;
			return false;
		}
		return true;
	}
	return true;

}

bool CollisionElipse::collisions(CollisionElipse* other){
	int x_dist = this->x_center - other->x_center;
	x_dist = abs(x_dist);
	int y_dist = this->y_center - other->y_center;
	y_dist = abs(y_dist);
	int center_dist = this->radius + other->radius;
	if(center_dist<x_dist || center_dist<y_dist)
		return false;
	int dist= x_dist*x_dist + y_dist*y_dist;
	center_dist = center_dist * center_dist;
	if(dist>center_dist)
		return false;
	return true;
}

CollisionElipse::~CollisionElipse() {
	// TODO Auto-generated destructor stub
}

