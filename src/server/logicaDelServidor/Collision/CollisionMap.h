/*
 * CollisionMap.h
 *
 *  Created on: 3/11/2016
 *      Author: usuario
 */

#ifndef COLLISIONMAP_H_
#define COLLISIONMAP_H_
#include <list>
#include <map>
class Collisionable;
using namespace std;
class CollisionMap {
struct Double{ int divs[2];};
struct NewMove{
	int oldBegining;
	int oldEnding;
	int newBegining;
	int newEnding;
};
public:
	map<Collisionable*,Double> collisionablesMap;
	map<int,list<Collisionable*>*> mapDivisions;
	list<Collisionable*>::iterator colIter;
	int len;
	int divisions;
	int divsSize;
	CollisionMap(int,int);
	void resetCollisionable(Collisionable*);
	void removeCollisionable(Collisionable*);
	void addNewCollisionable(Collisionable*);
	bool moveAttemptCollisionable(Collisionable*);
	void moveCollisionable(Collisionable*,NewMove);
	virtual ~CollisionMap();
};

#endif /* COLLISIONMAP_H_ */
