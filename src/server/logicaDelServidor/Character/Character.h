/*
 * Character.h
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <string>
#include <vector>
#include "../../../common/utils/Constants.h"
#include "../GameRelated/Parallax.h"
#include "CharactersRequest.h"
#include "../Animation/AnimationsRequest.h"
#include "../Animation/Animation.h"
#include "../Collision/Collisionable.h"
using namespace std;
class Character:public Collisionable{
public:
	int healthPoints;
	bool alive;
	bool dead;
	bool onScreen;
	Character();
	virtual ~Character();
	virtual bool isConnected() = 0;
	virtual bool hasID(std::string&)= 0;
	virtual std::string getFrame() = 0;
	virtual int getXPos(std::Parallax*) = 0;
	virtual int getYPos() = 0;
	virtual std::string getInfo() = 0;
	virtual void collisioned(Collisionable*)=0;
	virtual int getDisplacement()= 0;
	virtual int getLeftLimit()= 0;
	virtual int getRightLimit() =0;
	virtual bool collisionWith(Collisionable*) =0;
	virtual bool collisionWith(MainCharacter*) =0;
	virtual bool collisionWith(EnemyCharacter*)=0;
	virtual bool collisionWith(Animation*) =0;
	virtual bool appearsOnScreen()=0;
	virtual void die()=0;
	void recieveDamage(int);
	std::string& getIntroductionMessage();
	std::string& getExistingMessage();
	void setIntroductionMessage(const std::string);
	void setExistingMessage(const std::string);
	void setCharactersRequest(CharactersRequest*);
	void setActionsList();
	Animation* getNewAction();
	void setAnimationsRequest(AnimationsRequest*);
	virtual std::string& getCharacterID();
	virtual std::string& getCharacterImage();
	virtual void setCharacterID(const std::string& characterID);
	virtual void setCharacterImage(const std::string& imagePath);
	std::string introductionMessage;
	std::string existingMessage;
	list<Animation*>* playerActions;
	list<Animation*>::iterator iter;
	CharactersRequest* requestHandler;
	AnimationsRequest* animsRequestHandler;
	std::string imagePath;
	std::string characterID;
};
#endif /* CHARACTER_H_ */
