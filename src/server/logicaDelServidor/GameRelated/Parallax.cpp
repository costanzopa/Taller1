/*
 * Parallax.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: rodri
 */

#include "Parallax.h"


using namespace std;

Parallax::Parallax() {
	position = 0;
	min = 0; // 99999;
	max = 0;
	anchoPantalla = utils::SCREEN_WIDTH;
}

int Parallax :: getPosition(){
	return position;
}

void Parallax::startMinMax(){
	min = 99999;
	max = 0;
}
void Parallax::resetParallax(){
	this->min = 0;
	this->max = 99999;
	this->position=0;
}

void Parallax::processPosition(int characterPosition){
	if(characterPosition < this->min)
		this->min = characterPosition;
	if(characterPosition > this->max)
		this->max = characterPosition;
}

void Parallax::endMinMax(){
	int newPos =  (min+max)/2;
	if(min == 99999)
		return;
	//if(newPos >= position)
		this->position = newPos;//<<1; //Podria usar shifteo. Superoptimizacion (?)
	stringstream out;
	out << this->position;
	//cout << out.str() << endl;

	if(this->position > (utils::LEVEL_LENGHT - anchoPantalla/2))//utils::LEVEL_LENGHT - utils::SCREEN_WIDTH/2))
		this->position = utils::LEVEL_LENGHT - anchoPantalla/2;
}

Parallax::~Parallax() {
	// TODO Auto-generated destructor stub
}
