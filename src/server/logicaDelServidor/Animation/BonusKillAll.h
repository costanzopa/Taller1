/*
 * BonusKillAll.h
 *
 *  Created on: 16/11/2016
 *      Author: usuario
 */

#ifndef BONUSKILLALL_H_
#define BONUSKILLALL_H_

#include "Bonus.h"

class BonusKillAll: public Bonus {
public:
	BonusKillAll(int x,int y,int screenPosition,CollisionMap*,AnimationsRequest*);
	virtual ~BonusKillAll();
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

#endif /* BONUSKILLALL_H_ */
