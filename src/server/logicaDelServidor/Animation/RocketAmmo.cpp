/*
 * RocketAmmo.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "RocketAmmo.h"

int RocketAmmo::newId = 0;
namespace std {

RocketAmmo::RocketAmmo(int x,int y,int screenPosition,CollisionMap* map,AnimationsRequest* requester):
	BonusAmmo(x,y,screenPosition,map,requester),id(newId++){
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::ROCKET_AMMO);
	id.append(str);
	this->setAnimationID(id);

	this->type.append(utils::ROCKET_AMMO);

}
bool RocketAmmo::collisionWith(MainCharacter* other){
	if(this->active){
		this->activateBonus();
		this->active = false;
		other->weapons->totalBullets[1]+=2;
	}
	return false;
}
RocketAmmo::~RocketAmmo() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
