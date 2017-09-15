/*
 * FlameAmmo.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#include "FlameAmmo.h"

int FlameAmmo::newId = 0;
namespace std {

FlameAmmo::FlameAmmo(int x,int y,int screenPosition,CollisionMap* map,AnimationsRequest* requester):
	BonusAmmo(x,y,screenPosition,map,requester),id(newId++){
	std::stringstream ss;
	ss << newId;
	std::string str = ss.str();
	std::string id;
	id.append(utils::SINGLE_AMMO);
	id.append(str);
	this->setAnimationID(id);

	this->type.append(utils::SINGLE_AMMO);

}
bool FlameAmmo::collisionWith(MainCharacter* other){
	if(this->active){
		this->activateBonus();
		this->active = false;
		other->weapons->totalBullets[2]+=4;
	}
	return false;
}
FlameAmmo::~FlameAmmo() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
