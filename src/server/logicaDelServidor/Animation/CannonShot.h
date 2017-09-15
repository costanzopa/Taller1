/*
 * CannonShot.h
 *
 *  Created on: Nov 23, 2016
 *      Author: mario
 */

#ifndef SERVER_LOGICADELSERVIDOR_ANIMATION_CANNONSHOT_H_
#define SERVER_LOGICADELSERVIDOR_ANIMATION_CANNONSHOT_H_

#include "Animation.h"
#include "../GameRelated/Parallax.h"
#include "../GameRelated/CharacterMap.h"
#include "../../../common/utils/Constants.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"

class CannonShot: public Animation {
	enum HorizontalDirection { right , left};
public:
	bool inAction;
	int inclination;
	int speed;
	HorizontalDirection x_dir;
	int anchoPantalla;
	int x;
	int y;
	int x_vel;
	int y_vel;
	int bulletFrame;
	int screenPosition;
	int dissapearingFrames;
	int sequence_select;
	std::string type;
	std::string ID;
	CollisionElipse* shot;
	CollisionRectangle* trail;
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	CannonShot(int,int,int,int,int,CollisionMap*,AnimationsRequest*,std::string);
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
	virtual ~CannonShot();
private:
	static int newId;
	const int id;


};

#endif /* SERVER_LOGICADELSERVIDOR_ANIMATION_CANNONSHOT_H_ */
