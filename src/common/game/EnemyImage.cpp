/*
 * EnemyImage.cpp
 *
 *  Created on: 4/11/2016
 *      Author: usuario
 */

#include "EnemyImage.h"

EnemyImage::EnemyImage(SDL_Renderer* renderer,std::string path, float scale) {
	this->scale = scale;
	texture = new LTexture(renderer,path,scale);
	connected = true;
	renderedState = true;
	isDead = false;
	lastState = 1;
	flip = SDL_FLIP_NONE;
}
void EnemyImage::setStatus(int frame){
	this->setFrameProperties(frame);
}
EnemyImage::~EnemyImage() {
	delete texture;
}

