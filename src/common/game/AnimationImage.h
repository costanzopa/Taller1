/*
 * AnimationImage.h
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#ifndef ANIMATIONIMAGE_H_
#define ANIMATIONIMAGE_H_
#define ANIMATION_FRAMES 41
#include "GameImage.h"
#include "../utils/Constants.h"
#include <list>
#include <pthread.h>
using namespace std;

class AnimationImage: public GameImage {
struct ImageConfig{
	std::string id;
	int x;
	int y;
	int frame;
};
public:
	pthread_mutex_t mutex_lock;
	SDL_Rect gSpriteClips[ ANIMATION_FRAMES ];
	AnimationImage();
	void addNewCopy(const std::string&,int,int,int);
	void setPosition(const std::string& id,int x,int y,int frame);
	void removeAnimation(std::string&);
	virtual ~AnimationImage();
	virtual void render();
	list<ImageConfig*>* imageCopies;
	list<ImageConfig*>::iterator iter;
private:
	void lock(){ pthread_mutex_lock(&mutex_lock);}
	void unlock(){ pthread_mutex_unlock(&mutex_lock);}
};

#endif /* ANIMATIONIMAGE_H_ */
