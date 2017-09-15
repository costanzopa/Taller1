/*
 * BonusHeal.h
 *
 *  Created on: Nov 22, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_BONUSHEAL_H_
#define SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_BONUSHEAL_H_

#include "Bonus.h"

namespace std {

class BonusHeal: public Bonus {
public:
	BonusHeal(int x,int y,int screenPosition,CollisionMap*,AnimationsRequest*);
	virtual ~BonusHeal();
	void activateBonus();
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	virtual void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual std::string getType();
	virtual bool isConnected();
	virtual std::string getFrame();
	virtual int getXPos(std::Parallax*);
	virtual int getYPos();
	CollisionFigure* bonusBox;
	int anchoPantalla;
	int screenPosition;
	int x;
	int y;
	std::string type;
private:
	static int newId;
	const int id;
};
} /* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_ANIMATION_BONUSHEAL_H_ */
