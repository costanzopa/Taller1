/*
 * Bonus.h
 *
 *  Created on: 18/11/2016
 *      Author: usuario
 */

#ifndef BONUS_H_
#define BONUS_H_

#include "Animation.h"

class Bonus: public Animation {
public:
	Bonus();
	virtual bool collisionWith(Collisionable*)= 0;
	virtual bool collisionWith(MainCharacter*)= 0;
	virtual bool collisionWith(EnemyCharacter*)= 0;
	virtual bool collisionWith(Animation*)= 0;
	virtual void collisioned(Collisionable*)= 0;
	virtual int getDisplacement()= 0;
	virtual int getLeftLimit()= 0;
	virtual int getRightLimit()= 0;
	virtual std::string getType()= 0;
	virtual bool isConnected()= 0;
	virtual std::string getFrame()= 0;
	virtual int getXPos(std::Parallax*)= 0;
	virtual int getYPos()= 0;
	virtual ~Bonus();
	void activateEffect();
	bool used;
};

#endif /* BONUS_H_ */
