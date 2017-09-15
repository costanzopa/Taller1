/*
 * AnimationImage.cpp
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#include "AnimationImage.h"
#include <iostream>
using namespace std;
AnimationImage::AnimationImage() {
	this->imageCopies = new list<ImageConfig*>();
	pthread_mutex_init(&mutex_lock,NULL);

}

void AnimationImage::addNewCopy(const std::string& id,int x,int y,int frame){
	ImageConfig* copy = new ImageConfig;
	copy->x = x;
	copy->y = y;
	copy->id = id;
	copy->frame = frame;
	this->imageCopies->push_back(copy);
}
void AnimationImage::removeAnimation(std::string& ID){
	list<ImageConfig*>::iterator iter1;
	iter1 = this->imageCopies->begin();
	while(iter1 != this->imageCopies->end()){
		if((*iter1)->id.compare(ID)==0){
			this->lock();
			ImageConfig* toErase = *iter1;
			imageCopies->erase(iter1);
			this->unlock();
			delete toErase;
			break;
		}

		iter1++;
	}
}
void AnimationImage::setPosition(const std::string& id,int x,int y,int frame){
	list<ImageConfig*>::iterator iter1;
	iter1 = this->imageCopies->begin();
	while(iter1 != this->imageCopies->end()){
		if((*iter1)->id.compare(id)==0){
			this->lock();
			(*iter1)->x =x;
			(*iter1)->y =y;
			(*iter1)->frame =frame;
			this->unlock();
			break;
		}

		iter1++;
	}

}
void AnimationImage::render(){
	//cout<<"We render"<<endl;
	iter = this->imageCopies->begin();
	while(iter != this->imageCopies->end()){
		//cout<<"Vamos a renderizar"<<endl;
		this->lock();
		this->texture->render(this->gSpriteClips + (*iter)->frame,SDL_FLIP_NONE,(*iter)->x-3,(*iter)->y-5);
		this->unlock();
		//cout<<"Renderizo"<<endl;
		iter++;
	}
}
AnimationImage::~AnimationImage() {
	if(this->imageCopies->size() > 0) {
		list<ImageConfig*>::iterator iter1;
		iter1 = this->imageCopies->begin();
		while(iter1 != this->imageCopies->end()){
			ImageConfig* toErase = *iter1;
			imageCopies->erase(iter1);
			delete toErase;
			iter1++;
		}
	}
	delete imageCopies;
	delete texture;
}

