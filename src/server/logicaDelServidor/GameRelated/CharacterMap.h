/*
 * CharacterMap.h
 *
 *  Created on: Nov 16, 2016
 *      Author: rodri
 */

#ifndef SRC_SERVER_LOGICADELSERVIDOR_GAMERELATED_CHARACTERMAP_H_
#define SRC_SERVER_LOGICADELSERVIDOR_GAMERELATED_CHARACTERMAP_H_

#include <string>
#include <map>
#include "../Character/MainCharacter.h"

namespace std {

class CharacterMap {
public:
	CharacterMap();
	static void addCharacter(string,MainCharacter*);
	static void addPoints(string,int);
	static int getTotalPoints(string);
	static int getPoints(string);
	static bool teamWon(string);
	virtual ~CharacterMap();

private:
	static map<string, MainCharacter*> characters;
	static int maxPoints;
};

}/* namespace std */

#endif /* SRC_SERVER_LOGICADELSERVIDOR_GAMERELATED_CHARACTERMAP_H_ */
