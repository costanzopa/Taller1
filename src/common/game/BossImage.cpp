/*
 * BossImage.cpp
 *
 *  Created on: 21/11/2016
 *      Author: usuario
 */

#include "BossImage.h"

BossImage::BossImage(SDL_Renderer* renderer,std::string path, float scale) {
	this->scale = scale;
	texture = new LTexture(renderer,path,scale);
	connected = true;
	renderedState = true;
	isDead = false;
	lastState = 1;
	flip = SDL_FLIP_NONE;
}
BossImage::~BossImage() {
	delete texture;
}

