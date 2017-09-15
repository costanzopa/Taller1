/*
 * Weapons.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: rodri
 */

#include "Weapons.h"

Weapons::Weapons() {
	currentWeapon = 0;
}

void Weapons::cycleNext(){
	currentWeapon++;
	if(currentWeapon >= NUMBER_OF_GUNS)
		currentWeapon = 0;
}

void Weapons::cyclePrevious(){
	currentWeapon--;
	if(currentWeapon < 0)
		currentWeapon = NUMBER_OF_GUNS -1;
}

bool Weapons::shoot(){
	bulletsLeft[currentWeapon]--;
	if(bulletsLeft[currentWeapon] == 0){
		if(totalBullets[currentWeapon]<=magazine[currentWeapon]){
			if(totalBullets[currentWeapon] == 0) // Ya lo chequea MainCharacter
				return false;
			bulletsLeft[currentWeapon] = totalBullets[currentWeapon];
			totalBullets[currentWeapon] = 0;
		}
		else{
			bulletsLeft[currentWeapon] = magazine[currentWeapon];
			totalBullets[currentWeapon] -= magazine[currentWeapon];
		}
		return true;
	}
	return false;
}

bool Weapons::hasAmmo(){
	return bulletsLeft[currentWeapon]!=0;
}


int Weapons::getBulletsLeft(){
	return this->bulletsLeft[currentWeapon];
}

int Weapons::getTotalBullets(){
	return this->totalBullets[currentWeapon];
}



Weapons::~Weapons() {
	// TODO Auto-generated destructor stub
}

