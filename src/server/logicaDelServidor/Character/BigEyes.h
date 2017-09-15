/*
 * BigEyes.h
 *
 *  Created on: Nov 20, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_CHARACTER_BIGEYES_H_
#define SRC_SERVER_LOGICADELSERVIDOR_CHARACTER_BIGEYES_H_

#include "EnemyCharacter.h"
#include "../Animation/EyeLaser.h"
#include "../Animation/BigEyeBomb.h"

namespace std {
class BigEyes: public EnemyCharacter {
	enum Direction {right , left};
public:
	BigEyes(float,std::string,int,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	virtual void nextMove();
	virtual std::string getFrame();
	virtual ~BigEyes();

private:
	int sequence_selector;
	int sequence_offset;
	int initialPosition;
	int maxDistance;
	int positionToGo;
	bool halfWalked;
	bool returned;
	bool attacking;
	Direction direction;
	int palletWidth;
	int palletHeight;
	int eyeRadio;
	CollisionRectangle* sidePallet1;
	CollisionRectangle* sidePallet2;
	CollisionElipse* eye;
	int laserFrame;
	int laserCount;
	bool firing;
	int laserBullets;
	int firingWait;
	void dropBomb();
	int getXLaserVel();
	void startFiring();
	void shootLaser();

	int getExtraFrameInt();
	int getFrameInt();
	void selectCurrentSequence();
	void attack();
};

} /* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_CHARACTER_BIGEYES_H_ */
