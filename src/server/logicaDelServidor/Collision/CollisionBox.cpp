/*
 * CollisionBox.cpp
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#include "CollisionBox.h"
#include <iostream>
using namespace std;
CollisionBox::CollisionBox(){
	this->hitBox = new list<CollisionFigure*>();
}
void CollisionBox::addNewHitbox(CollisionFigure* figure){
	this->hitBox->push_back(figure);
}
void CollisionBox::moveCollisionBox(int x,int y){
	iter = this->hitBox->begin();
	while(iter != this->hitBox->end()){
		(*iter)->setPosition(x,y);
		iter++;
	}
}
bool CollisionBox::collisions(CollisionBox* other){
	list<CollisionFigure*>::iterator iter1;
	iter = this->hitBox->begin();
	while(iter!=this->hitBox->end()){
		iter1 = other->hitBox->begin();
		while(iter1!=other->hitBox->end()){
			if((*iter)->collisions((*iter1)))
				return true;
			iter1++;
		}
		iter++;
	}
	return false;
}
CollisionBox::~CollisionBox() {
	// TODO Auto-generated destructor stub
}

