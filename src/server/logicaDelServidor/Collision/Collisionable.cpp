/*
 * Collisionable.cpp
 *
 *  Created on: 3/11/2016
 *      Author: usuario
 */

#include "Collisionable.h"

Collisionable::Collisionable() {
	// TODO Auto-generated constructor stub

}
void Collisionable::setCollisionMap(CollisionMap* map){
	this->collisionMap = map;
	this->collisionMap->addNewCollisionable(this);
}
void Collisionable::setCollisionBox(){
	this->hitBox = new CollisionBox();
}
bool Collisionable::collisions(Collisionable* collisionable){
	if(this->hitBox->collisions(collisionable->hitBox)){
		return this->collisionWith(collisionable);
	}
	return false;
}
Collisionable::~Collisionable() {
	// TODO Auto-generated destructor stub
}

