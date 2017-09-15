/*
 * SingleShot.h
 *
 *  Created on: 1/11/2016
 *      Author: usuario
 */

#ifndef SINGLESHOT_H_
#define SINGLESHOT_H_
 
  #include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>

#include "../Animation/Animation.h"
#include "../GameRelated/Parallax.h"
#include "../GameRelated/CharacterMap.h"
#include "../../../common/utils/Constants.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"

 
class MainCharacter;
class EnemyCharacter;

class SingleShot: public Animation{
	enum HorizontalDirection { right , left};
	enum VerticalDirection { horizontal, up , diagonal};
public:
	bool inAction;
	int inclination;
	int speed;
	int anchoPantalla;
	int x;
	int y;
	int screenPosition;
	int dissapearingFrames;
	std::string type;
	std::string ID;
	CollisionElipse* shot;
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	HorizontalDirection x_dir;
	VerticalDirection y_dir;
	SingleShot(int,int,int,int,int,CollisionMap*,AnimationsRequest*,std::string);
	virtual void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual std::string getType();
	virtual ~SingleShot();
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

#endif /* SINGLESHOT_H_ */
