/*
 * ZombieShot.h
 *
 *  Created on: 18/11/2016
 *      Author: usuario
 */

#ifndef ZOMBIESHOT_H_
#define ZOMBIESHOT_H_

#include "Animation.h"
#include <vector>
#include "../GameRelated/Parallax.h"
#include "../GameRelated/CharacterMap.h"
#include "../../../common/utils/Constants.h"
#include "../Character/EnemyCharacter.h"
#include "../Character/MainCharacter.h"

class ZombieShot: public Animation {
public:
	ZombieShot(std::string,int,int,int,int,std::vector<int>*,CollisionMap*,AnimationsRequest*);
	virtual ~ZombieShot();
	enum HorizontalDirection { right , left};
public:
	bool inAction;
	int inclination;
	int speed;
	int anchoPantalla;
	int x;
	int y;
	int current_y;
	int frameNumber;
	std::vector<int>* shot_table;
	int shot_table_index;
	int screenPosition;
	int dissapearingFrames;
	int sequence_selector;
	std::string type;
	CollisionElipse* shot;
	int hasToDescend;
	int getFrameInt();
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	HorizontalDirection x_dir;
	std::vector<int>* y_table;
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
	void moveNextHeight();
	static int newId;
	const int id;
};

#endif /* ZOMBIESHOT_H_ */
