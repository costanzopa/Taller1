/*
 * GroundFloor.cpp
 *
 *  Created on: 20/11/2016
 *      Author: usuario
 */

#include "GroundFloor.h"
#include <iostream>
using namespace std;
GroundFloor::GroundFloor(int x,int y,int width,int height,CollisionMap* map){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	floor = new CollisionRectangle(x,y,width,height,0,0);
	this->setCollisionBox();
	this->hitBox->addNewHitbox(floor);
	this->setCollisionMap(map);

}

bool GroundFloor::collisionWith(Collisionable* other){
	return other->collisionWith(this);
}
bool GroundFloor::collisionWith(MainCharacter* other){
	return true;
}
bool GroundFloor::collisionWith(EnemyCharacter* other){
	return false;
}
bool GroundFloor::collisionWith(Animation* other){
	return false;
}
void GroundFloor::collisioned(Collisionable*){
	return;
}
int GroundFloor::getDisplacement(){
	return 0;
}
int GroundFloor::getLeftLimit(){
	return this->x;
}
int GroundFloor::getRightLimit(){
	return this->x+width;
}

GroundFloor::~GroundFloor() {
	// TODO Auto-generated destructor stub
}

