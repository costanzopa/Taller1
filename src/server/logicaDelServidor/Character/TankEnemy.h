/*
 * MeleeEnemy.h
 *
 *  Created on: 31/10/2016
 *      Author: usuario
 */

#ifndef TANKENEMY_H_
#define TANKENEMY_H_

#include "EnemyCharacter.h"

class TankEnemy: public EnemyCharacter {
enum Direction {right , left};
public:
	TankEnemy(float,std::string,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	virtual void nextMove();
	virtual std::string getFrame();
	virtual ~TankEnemy();
private:
	int tankWidth;
	int tankHeight;
	int cannonWidth;
	int cannonHeight;
	CollisionRectangle* tank;
	CollisionRectangle* cannon;
	int range;
	int sequence_selector;
	int sequence_offset;
	int heavyWeaponReload;
	int lightWeaponReload;
	int firingFrames;
	int turningFrames;
	int	movingFrames;
	int idleFrames;
	bool attacking;
	bool turning;
	bool idle;
	bool moving;
	Direction direction;
	int getFrameInt();
	void shootCanon();
	void shootLightWeapon();
	void selectCurrentSequence();
	void attack();
};

#endif /* MELEEENEMY_H_ */
