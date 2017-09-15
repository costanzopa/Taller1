/*
 * CharacterMap.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: rodri
 */

#include "CharacterMap.h"

int CharacterMap::maxPoints;
map<string, MainCharacter*> CharacterMap::characters;

namespace std {

CharacterMap::CharacterMap() {
	maxPoints = 0;
}

void CharacterMap::addCharacter(string ID,MainCharacter* character){
	characters[ID] = character;
}

void CharacterMap::addPoints(string ID, int points){
	if(CharacterMap::characters.find(ID) == CharacterMap::characters.end()) {
		return;
	}
	CharacterMap::characters.find(ID)->second->addPoints(points);
}
int CharacterMap::getTotalPoints(string ID){
	if(CharacterMap::characters.find(ID) == CharacterMap::characters.end()) {
		return -1;
	}
	int team = CharacterMap::characters.find(ID)->second->team;
	int totalPoints = 0;
	for (map<string,MainCharacter*>::iterator it=characters.begin(); it!=characters.end(); ++it){
	   if((it->second->team == team))
			   totalPoints += it->second->points;
	}
	if(totalPoints > maxPoints){
		maxPoints = totalPoints;
	}
	return totalPoints;
}
bool CharacterMap::teamWon(string ID){
	int points = CharacterMap::getTotalPoints(ID);
	if(points == maxPoints)
		return true;
	return false;
}
int CharacterMap::getPoints(string ID){
	if(CharacterMap::characters.find(ID) == CharacterMap::characters.end()) {
		return -1;
	}
	return CharacterMap::characters.find(ID)->second->points;
}

CharacterMap::~CharacterMap() {
}

} /* namespace std */
