/*
 * RocketAmmo.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETAMMO_H_
#define SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETAMMO_H_

#include "BonusAmmo.h"

namespace std {

class RocketAmmo: public BonusAmmo {
public:
	RocketAmmo(int x,int y,int screenPosition,CollisionMap*,AnimationsRequest*);
	virtual bool collisionWith(MainCharacter*);
	virtual ~RocketAmmo();

private:
	static int newId;
	const int id;
};

} /* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_ROCKETAMMO_H_ */
