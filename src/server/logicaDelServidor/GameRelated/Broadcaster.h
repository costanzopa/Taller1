/*
 * Broadcaster.h
 *
 *  Created on: 1/10/2016
 *      Author: usuario
 */

#ifndef BROADCASTER_H_
#define BROADCASTER_H_

#include <list>
#include <vector>
#include <unistd.h>
#include <string>
#include <sstream>
#include <algorithm>
#include "../Character/Character.h"
#include "../Character/MainCharacter.h"
#include "../GameRelated/CharacterMap.h"
#include "ReloadReady.h"
#include "Parallax.h"
#include "../../../estructurasDeDatos/CharactersInGame.h"
#include "../../../estructurasDeDatos/AnimationsInGame.h"
#include "../../../common/threads/Thread.h"
#include "../../../estructurasDeDatos/MessageList.h"
#include "../../../estructurasDeDatos/User.h"
#include "../../../estructurasDeDatos/Node.h"
#include "../../../common/utils/Constants.h"


using namespace std;

class Broadcaster: public threads:: Thread{
public:
	list<Character*>* gameParticipants;
	Parallax* gameBackground;
	list<User*>* connectedUsers;
	MessageList* newStatus;
	MessageList* incomingMessages;
	User* reconnectingPlayer;
	string backgroundPath;
	ReloadReady* reloader;
	bool mustBeReloaded;
	CharactersInGame* currentLevel;
	AnimationsInGame* currentAnimations;
	bool canBeReloaded;
	void reloadGame();
	void setLevel(CharactersInGame*);
	void setAnimations(AnimationsInGame*);
	void reconnectPlayer(User*);
	Broadcaster(MessageList*,list<Character*>*,Parallax*,list<User*>*,string,MessageList*);
	virtual void stop();
	void setReloader(ReloadReady*);
	void broadcastNewGameTo(User*);
	void broadcastGameBegin();//Le avisa a todos que comenzara el juego y las posiciones de todos
	void broadcastNewStatus();//Le avisa a todos los jugadores las nuevas posiciones al final de la iteracion de todos en el mapa
	void broadcastNewInfo();
	void broadcastLevelInfo(list<MainCharacter*>*);
	void broadcastLevelInfoOver();
	void broadcastGameOver();
	void broadcastNewBackgroundStatus();
	void broadcastReload();
private:
	virtual void* process();
};



#endif /* BROADCASTER_H_ */
