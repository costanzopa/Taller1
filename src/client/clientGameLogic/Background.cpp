/*
 * Background.cpp
 *
 *  Created on: Sep 27, 2016
 *      Author: rodri
 */

#include "Background.h"
#include <string>
#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


using namespace std;

//  Los fondos de organizan uno atras de otro
//  siendo la posicion 0 la de mas atras


Background::Background(SDL_Renderer* gRenderer) {

	this->renderer = gRenderer;
	this->bgScale = 1.0;
}

Background::~Background() {
	for(int i=0;i<NRO_BACKGROUNDS;i++){
		delete background[i];
		//delete background2[i];
	}
}
void Background::startupBackgrounds(){
	for(int i=0;i<NRO_BACKGROUNDS;i++){
		if(!background[i]->loadImage())
			background[i]->loadFromFile(utils::BACKGROUND_ERROR_DIR);
	}
	this->relativeWidth =(float) this->bgScale*background[NRO_BACKGROUNDS-1]->texture->getWidth();
	//this->relativeWidth += utils::SCREEN_WIDTH*bgScale;
	//this->relativeWidth = utils::LEVEL_LENGHT;
}

void Background::setScale(float scale){
	bgScale = scale;
}

void Background::loadBackgrounds(){
	for(int i=0;i<NRO_BACKGROUNDS;i++){
		background[i] = new BackgroundImage(renderer,getPath(i),bgScale);
		if (background[i]==NULL)
			cout << "Error al cargar imagen" << endl;

		background[i]->setPosition(0,0);
	}
}

void Background::setDirectory(string& directory){
	this->levelPath = directory;
	this->loadBackgrounds();
}

void Background::render(){
	for(int i=0;i<NRO_BACKGROUNDS;i++){
		background[i]->render();
	}
}

void Background::modifyBackgroundPosition(std::string& coordinate) {
	int newPosition;
	sscanf(coordinate.c_str(), "%d", &newPosition);

	//float relativePos1 = newPosition/this->relativeWidth;

	for(int i=1; i<NRO_BACKGROUNDS ;i++){
		background[i]->setPosition(-(newPosition/(NRO_BACKGROUNDS-i)),0);
	}

}
string Background::getPath(int i){
	string path = this->levelPath;
	stringstream layer;
	path.append("layer");
	layer << i;
	path.append(layer.str());
	path.append(".png");

	//cout << endl << path << endl;
	return path;
}
string Background::getDefaultPath(int i){
	string path = utils::BACKGROUND_DIR;
	stringstream layer;
	path.append("layer");
	layer << i;
	path.append(layer.str());
	path.append(".png");

	//cout << endl << path << endl;
	return path;
}
