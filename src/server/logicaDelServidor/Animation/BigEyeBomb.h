/*
 * BigEyeBomb.h
 *
 *  Created on: 23/11/2016
 *      Author: usuario
 */

#ifndef BIGEYEBOMB_H_
#define BIGEYEBOMB_H_



#include "Animation.h"
#include "../GameRelated/Parallax.h"
#include "../GameRelated/CharacterMap.h"
#include "../../../common/utils/Constants.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"

class BigEyeBomb: public Animation {
public:
	virtual ~BigEyeBomb();
	bool inAction;
	int inclination;
	int speed;
	int anchoPantalla;
	int x;
	int y;
	int x_vel;
	int y_vel;
	int bulletFrame;
	int screenPosition;
	int dissapearingFrames;
	std::string type;
	std::string ID;
	CollisionElipse* shot;
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	BigEyeBomb(int,int,int,int,int,CollisionMap*,AnimationsRequest*,std::string);
	virtual void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual std::string getType();
	void nextPosition();
	void nextYPosition();
	virtual bool isConnected();
	virtual std::string getFrame();
	virtual int getXPos(std::Parallax*);
	virtual int getYPos();
	void setDirection(int);
	int getId();
private:
	static int newId;
	const int id;
};

#endif /* BIGEYEBOMB_H_ */
