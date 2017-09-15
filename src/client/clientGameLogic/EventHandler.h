/*
 * EventHandler.h
 *
 *  Created on: Oct 10, 2016
 *      Author: mario
 */

#ifndef CLIENT_CLIENTGAMELOGIC_EVENTHANDLER_H_
#define CLIENT_CLIENTGAMELOGIC_EVENTHANDLER_H_

#include <string>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameInputCommand.h"
#include "../../common/threads/Thread.h"
#include "GameReloader.h"

using namespace std;

namespace client {

class EventHandler: public threads::Thread{
public:

	EventHandler(Client* client, std::string& srv);
	void setGameReloader(GameReloader*);
	GameInputCommand* getCommand(SDL_Event e);
	virtual void stop();
	bool getKeepGoing();

	virtual ~EventHandler();

private:
	void init();
	virtual void* process();
	string getKey(SDL_Event e);
	string getKey(Uint32 type, SDL_Keycode keyCode);
	GameReloader* gameReloader;
	map<string, GameInputCommand*> commands;
	Client* client;
	std::string server;
	bool keepGoing;

};

} /* namespace client */

#endif /* CLIENT_CLIENTGAMELOGIC_EVENTHANDLER_H_ */
