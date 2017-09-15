/*
 * AnimationsInGame.h
 *
 *  Created on: 2/11/2016
 *      Author: usuario
 */

#ifndef ANIMATIONSINGAME_H_
#define ANIMATIONSINGAME_H_
#include <pthread.h>
#include <iostream>
#include "../server/logicaDelServidor/Animation/Animation.h"
#include "../server/logicaDelServidor/GameRelated/Parallax.h"
#include <list>
#include <string>
#include "Node.h"

class AnimationsInGame {
public:
	AnimationsInGame();
	list<Animation*>* activeAnimations;
	list<Animation*>* newAnimations;
	pthread_mutex_t mutex;
	list<Animation*>:: iterator broadcastIter;
	list<Animation*>:: iterator newAnimIter;
	Parallax* gameBackground;
	void setBackground(Parallax*);
	Animation* getAnimation(std::string);
	void resetAnimations();
	void addNewAnimation(Animation*);
	void removeAnimation(std::string);
	void initBroadCast();
	std::string getNewAnimationSettings();
	string getAnimationsMessages();
	bool finished();
	virtual ~AnimationsInGame();
private:
		void lock(){ pthread_mutex_lock(&mutex);}
		void unlock(){ pthread_mutex_unlock(&mutex);}
};

#endif /* ANIMATIONSINGAME_H_ */
