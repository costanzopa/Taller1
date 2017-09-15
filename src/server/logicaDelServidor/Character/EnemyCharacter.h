/*
 * EnemyCharacters.h
 *
 *  Created on: 29/10/2016
 *      Author: usuario
 */

#ifndef ENEMYCHARACTERS_H_
#define ENEMYCHARACTERS_H_
#include "Character.h"
#include "MainCharacter.h"
 #include "../Animation/SingleShot.h"
#include <string>

class SingleShot;
class EnemyCharacter: public Character{
	enum Direction { right , left };
public:
	int damage;
	MainCharacter* charTarget;
	list<MainCharacter*>* charsInGame;
	int targetPosition;
	int x;
	int screenPosition;
	int y;
	int velocidad;
	int frame_selector;
	int anchoPantalla;
	bool appearedOnScreen;
	bool moving;
	float scale;
	Direction currentDirection;
	virtual bool isConnected();
	EnemyCharacter(float,std::string,int,int,list<MainCharacter*>*,CharactersRequest*,AnimationsRequest*,CollisionMap*);
	void setTarget();
	virtual void die();
	virtual bool appearsOnScreen(){return appearedOnScreen;}
	void killAll();
	virtual bool collisionWith(Collisionable*);
	virtual bool collisionWith(MainCharacter*);
	virtual bool collisionWith(EnemyCharacter*);
	virtual bool collisionWith(Animation*);
	virtual bool hasID(std::string&);
	virtual std::string getInfo();
	virtual void collisioned(Collisionable*);
	virtual int getDisplacement();
	virtual int getLeftLimit();
	virtual int getRightLimit();
	virtual std::string getFrame();
	void setCharacterPosition(int,int);
	void setCharacterScreenPosition(int);
	virtual Animation* getNewAction();
	virtual int getXPos(std::Parallax*);
	virtual int getYPos();
	virtual ~EnemyCharacter();
protected:
	virtual void nextMove() =0;
};

#endif /* ENEMYCHARACTERS_H_ */
