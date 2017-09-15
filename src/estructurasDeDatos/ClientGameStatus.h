/*
 * GameStatus.h
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */

#ifndef CLIENTGAMESTATUS_H_
#define CLIENTGAMESTATUS_H_
#include <list>
#include <map>
#include "../common/game/GameImage.h"
#include "../common/game/CharacterImage.h"
#include "../common/game/MeleeEnemyImage.h"
#include "../common/game/RangeEnemyImage.h"
#include "../common/utils/Constants.h"
#include "../common/game/LTexture.h"


class ClientGameStatus{
	list<GameImage*>* characterList;
	map<std::string,GameImage*> characterMap;
	string user;
public:
	ClientGameStatus(string userName,SDL_Renderer* renderer,float scale);
	~ClientGameStatus();
	void startupImages();
	void addCharacter(std::string&,GameImage*);
	void modifyEnemyPosition(std::string&,std::string&,std::string&,std::string&);
	void modifyBossPosition(std::string&,std::string&,std::string&,std::string&);
	void removeCharacter(std::string&);
	void removeEnemy(std::string&);
	void removeBoss(std::string&);
	void removeAnimation(std::string&,std::string&);
	void addNewAnimation(std::string&,std::string&,std::string&,std::string&);
	void modifyAnimation(std::string&,std::string&,std::string&,std::string&,std::string&);
	void modifyCharacterPosition(std::string&,std::string&,std::string&,std::string&);
	void renderCharacters();
	SDL_Renderer* renderer;
};

#endif /* GAMESTATUS_H_ */
