/*
 * CollisionMap.cpp
 *
 *  Created on: 3/11/2016
 *      Author: usuario
 */

#include "CollisionMap.h"
#include "Collisionable.h"
#include <iostream>

CollisionMap::CollisionMap(int size,int divs) {
	this->len = size;
	this->divisions = divs;
	this->divsSize = len/divisions;
	for(int i=0;i<divisions+5;i++){
		this->mapDivisions[i]= new list<Collisionable*>();
	}
	for(int i=-1;i>-10;i--){
			this->mapDivisions[i]= new list<Collisionable*>();
	}
}
void CollisionMap::resetCollisionable(Collisionable* other){
	this->removeCollisionable(other);
	cout<<"Termin de sacarme"<<endl;
	this->addNewCollisionable(other);
	cout<<"Termin de ponerme"<<endl;
}
void CollisionMap::removeCollisionable(Collisionable* collisionable){
	Double positions = this->collisionablesMap[collisionable];
	list<Collisionable*>:: iterator iter;
	//cout<<positions.divs[0]<<endl;
	//cout<<positions.divs[1]<<endl;
	list<Collisionable*>* toRemove;
	for (int i = positions.divs[0];i<=positions.divs[1];i++){
		toRemove = this->mapDivisions[i];
			iter = toRemove->begin();
			while(iter != toRemove->end()){
				if(*iter == collisionable){
					toRemove->erase(iter);
					break;
				}
				iter++;
			}
	}
	/*toRemove = this->mapDivisions[positions.divs[0]];
	iter = toRemove->begin();
	while(iter != toRemove->end()){
		if(*iter == collisionable){1
		}
		iter++;
	}
	if(positions.divs[1]!=positions.divs[0]){
		toRemove = this->mapDivisions[positions.divs[1]];
		iter = toRemove->begin();
		while(iter != toRemove->end()){
			if(*iter == collisionable){
				toRemove->erase(iter);
				break;
			}
			iter++;
		}
	}*/
	this->collisionablesMap.erase(collisionable);
}
void CollisionMap::addNewCollisionable(Collisionable* collisionable){
	int leftLimit = collisionable->getLeftLimit();
	int rightLimit = collisionable->getRightLimit();
	//cout<<"Left		"<<leftLimit<<endl;
	//cout<<"Right 	"<<rightLimit<<endl;
	int beginingDivision = leftLimit/this->divsSize;
	int endingDivision = rightLimit/this->divsSize;

	Double positions;
	positions.divs[0]= beginingDivision;
	positions.divs[1]= endingDivision;
	this->collisionablesMap[collisionable]= positions;
	for(int i = beginingDivision; i<=endingDivision; i++){
		this->mapDivisions[i]->push_back(collisionable);
	}
}
void CollisionMap::moveCollisionable(Collisionable* collisionable,NewMove move){
	Double positions = this->collisionablesMap[collisionable];
	positions.divs[0] = move.newBegining;
	positions.divs[1] = move.newEnding;
	colIter = this->mapDivisions[move.oldBegining]->begin();
	while((*colIter)!= collisionable)
		colIter++;
	this->mapDivisions[move.oldBegining]->erase(colIter);
	if(move.oldEnding!=move.oldBegining){
		colIter = this->mapDivisions[move.oldEnding]->begin();
		while((*colIter)!= collisionable)
			colIter++;
		this->mapDivisions[move.oldEnding]->erase(colIter);

	}
	this->mapDivisions[move.newBegining]->push_back(collisionable);
	if(move.newEnding!=move.newBegining){
		this->mapDivisions[move.newEnding]->push_back(collisionable);
	}
	this->collisionablesMap[collisionable]= positions;
}
bool CollisionMap::moveAttemptCollisionable(Collisionable* collisionable){
	//   (A) se mueve y colisiona con (B)
	int move = collisionable->getDisplacement();
	int leftLimit = collisionable->getLeftLimit();
	int rightLimit = collisionable->getRightLimit();
	//Me fijo si el  (A) personaje se esta moviendo para la derecha (X ascendentes)
	if(move>=0){
		Double colPositions = this->collisionablesMap[collisionable];
		int newPosition = move + rightLimit;
		//Si se mueve para la derecha (A) lo unico que me importa es el nuevo limite derecho el resto esta dentro del personaje (A)
		int newRightLimitDiv = newPosition/this->divsSize;
		//Me fijo si con el nuevo limite derecho estoy en una division nueva del mapa (Una a la derecha)
		list<Collisionable*>* collisioners = this->mapDivisions[newRightLimitDiv];
		colIter = collisioners->begin();
		while(colIter != collisioners->end()){
			if((*colIter)!= collisionable){
				if((*colIter)->collisions(collisionable))
					return false;
			}
			colIter++;
		}
		//Si no colisionamos nos movemos
		NewMove definiteMove;
		definiteMove.oldBegining = colPositions.divs[0];
		definiteMove.oldEnding = colPositions.divs[1];
		definiteMove.newEnding = (rightLimit+ move)/divsSize;
		definiteMove.newBegining = (leftLimit+ move)/divsSize;
		this->moveCollisionable(collisionable,definiteMove);
		return true;
	}else{
		Double colPositions = this->collisionablesMap[collisionable];
		int newPosition = move + leftLimit;
		int newLeftLimitDiv = newPosition/this->divsSize;
		list<Collisionable*>* collisioners = this->mapDivisions[newLeftLimitDiv];
		colIter = collisioners->begin();
		while(colIter != collisioners->end()){
			if((*colIter)!= collisionable){
					if((*colIter)->collisions(collisionable)){
						return false;
					}
			}
			colIter++;
		}
		NewMove definiteMove;
		definiteMove.oldBegining = colPositions.divs[0];
		definiteMove.oldEnding = colPositions.divs[1];
		definiteMove.newEnding = (rightLimit+ move)/divsSize;
		definiteMove.newBegining = (leftLimit+ move)/divsSize;
		this->moveCollisionable(collisionable,definiteMove);
		return true;
	}
}
CollisionMap::~CollisionMap() {
	// TODO Auto-generated destructor stub
}

