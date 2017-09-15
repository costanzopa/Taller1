/*
 * RocketLauncher.cpp
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#include "RocketLauncher.h"

RocketLauncher::RocketLauncher(int x,int y,int screenPosition,int dirX,int dirY,CollisionMap* map,AnimationsRequest* requester){
	this->setIntroductionMessage(utils::NEW_ANIMATION);
	this->setExistingMessage(utils::EXISTING_ANIMATION);
	this->setAnimationRequest(requester);
	this->setCollisionMap(map);
	this->setCollisionBox(x+19,y,31,9); // Podria ser mas chico
}

RocketLauncher::~RocketLauncher() {
	// TODO Auto-generated destructor stub
}

