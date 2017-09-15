/*
 * Animation.h
 *
 *  Created on: 1/11/2016
 *      Author: usuario
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_
#include "../GameRelated/Parallax.h"
#include "../Collision/Collisionable.h"
#include "AnimationsRequest.h"

class MainCharacter;

class Animation:public Collisionable{
public:
	int damage;
	int displacement;
	bool active;
	bool onScreen;
	bool dissapeared;
	Animation();
	virtual ~Animation();
	virtual bool isConnected() = 0;
	virtual std::string getFrame() = 0;
	std::string& getIntroductionMessage();
	std::string& getExistingMessage();
	void setIntroductionMessage(const std::string);
	void setExistingMessage(const std::string);
	virtual std::string& getAnimationID();
	virtual std::string& getAnimationImage();
	void destroyAnimation();
	virtual int getDisplacement()= 0;
	virtual int getLeftLimit()= 0;
	virtual int getRightLimit() =0;
	virtual std::string getType()=0;
	void setAnimationRequest(AnimationsRequest*);
	virtual void setAnimationImage(const std::string& imagePath);
	virtual void setAnimationID(const std::string& animationID);
	virtual int getXPos(std::Parallax*) = 0;
	virtual int getYPos() = 0;
	AnimationsRequest* requester;
private:
	std::string introductionMessage;
	std::string existingMessage;
	std::string imagePath;
	std::string animationID;
};

#endif /* ANIMATION_H_ */
