/*
 * MainCharacter.h
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#ifndef MAINCHARACTER_H_
#define MAINCHARACTER_H_

#include <list>
#include <iostream>
#include <sstream>
#include "../Animation/SingleShot.h"
#include "../Animation/RocketShot.h"
#include "../Animation/FlameShot.h"
#include "../Animation/EnemyChaser.h"
#include "../Animation/Weapons.h"
#include "Character.h"
 
class EnemyCharacter;
class MainCharacter: public Character {
	enum HorizontalDirection { right , left };
	enum VerticalDirection { horizontal , up , diagonal , down };
	enum CurrentGun { pistol , shotgun };
public:

	//Animation
	bool firing;
	bool reloading;
	bool changingWeapon;
	bool dying;
	int sequence_offset;
	int sequence_select;
	int frame_selector;
	int frame_offset;

	int longBodyWidth;
	int longBodyHeight;
	int shortBodyWidth;
	int shortBodyHeight;
	int crouchBodyWidth;
	int crouchBodyHeight;
	//Collision
	CollisionBox* secondaryBox;
	CollisionRectangle* crouch;
	CollisionRectangle* longBody;
	CollisionRectangle* shortBody;
	virtual bool isConnected();
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual void die();
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	virtual bool appearsOnScreen(){return true;}
	//Position
	std::vector<int>* jumping_table;
	int x;
	int current_y;
	int screenPosition;
	//int y;
	int floorLevel;
	int topLevel;
	int levelId;
	int velocidad;
	int jump_stage;
	int anchoPantalla;
	int displacement;
	int leftLimit;
	int rightLimit;
	bool jumping;
	bool moving;
	bool connected;
	int points;
	float scale;

	list<EnemyCharacter*>* enemies;
	void setEnemies(list<EnemyCharacter*>*);
	EnemyCharacter* getClosestEnemy();

	HorizontalDirection currentDirection;
	VerticalDirection verticalDirection;

	//Misc
	Weapons* weapons;
	std::string characterSelect;
	int team;

	MainCharacter(float,std::string&,int,std::vector<int>*,std::string,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	~MainCharacter();
	void addPoints(int);
	void healAll();
	void Disconnected();
	void Connected();
	int getFrameInt();
	void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual bool hasID(std::string&);
	void processAction(std::string&);
	void shoot();
	virtual std::string getFrame();
	virtual int getLegsFrame();
	void setCharacterPosition(int,int);
	void setCharacterScreenPosition(int);
	int getScreenPosition();
	virtual int getXPos(std::Parallax*);
	virtual int getYPos();
	virtual std::string getInfo();
	void setLevel(int);
	void setTeam(int);
private:
	void setTopLevel();
	void changeToWeapon();
	int getXShot();
	int getYShot();
	void selectCurrentSequence();
	void selectLegFrame();
	int getNextHeight();
	void falling();
	void stopJump(int);
	bool isInPlatform();
	void halt();
	void moveRight();
	void moveLeft();
	void crawl();
	void standUp();
	void lookUp();
	void lookRightFromUp();
	void cyclePreviousWeapon();
	void cycleNextWeapon();
};

#endif /* MAINCHARACTER_H_ */
