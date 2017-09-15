/*
 * GameRefresher.h
 *
 *  Created on: 17/09/2016
 *      Author: guido
 */

#ifndef GAMEREFRESHER_H_
#define GAMEREFRESHER_H_
#include <list>
#include "../../estructurasDeDatos/Node.h"
#include "../../estructurasDeDatos/ClientGameStatus.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Client.h"
#include "GameReloader.h"
#include "../../common/threads/Thread.h"
#include "Background.h"
#include "Information.h"
#include "../../common/game/TankEnemyImage.h"

using namespace client;

class GameRefresher: public threads::Thread{

public:
	bool gameReady;
	ClientGameStatus* gameStatus;
	Background* gameBackground;
	Information* gameInfo;
	//The window renderer
	GameReloader* reloader;
	SDL_Renderer* gRenderer;
	Client* communication;
	GameRefresher(ClientGameStatus*,Background*,Information*,SDL_Renderer*,GameReloader*);
	~GameRefresher();
	virtual void stop();
	void updateGameStatus(list<Node*>* updates);
	void setClient(Client*);
	void setScale(float scale);
private:
	virtual void* process();
	void processMessage(Node*);
	bool isEnemy(std::string&);
	void addNewCharacter(std::string&,std::string&);
	void addNewMeleeEnemy(std::string&,std::string&);
	void addNewRangeEnemy(std::string&,std::string&);
	void addNewUfoEnemy(std::string&,std::string&);
	void addNewTankEnemy(std::string&,std::string&);
	void addNewEyesEnemy(std::string&,std::string&);
	float scale;

};

#endif /* GAMEREFRESHER_H_ */
