/*
 * RocketLauncher.h
 *
 *  Created on: 11/11/2016
 *      Author: usuario
 */

#ifndef ROCKETLAUNCHER_H_
#define ROCKETLAUNCHER_H_

#include "Animation.h"

class RocketLauncher: public Animation {
	enum HorizontalDirection { right , left};
	enum VerticalDirection { horizontal, up , diagonal};
public:
	virtual ~RocketLauncher();
	bool inAction;
	int inclination;
	int speed;
	int anchoPantalla;
	int x;
	int y;
	int screenPosition;
	int dissapearingFrames;
	std::string type;
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(SingleShot*);
	HorizontalDirection x_dir;
	VerticalDirection y_dir;
	RocketLauncher(int,int,int,int,int,CollisionMap*,AnimationsRequest*,std::string);
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

};

#endif /* ROCKETLAUNCHER_H_ */
