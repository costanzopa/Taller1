/*
 * EventHandler.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: mario
 */

#include "EventHandler.h"

namespace client {

EventHandler::EventHandler(Client* client, std::string& srv) {
	this->init();
	this->client = client;
	server = srv;
	this->keepGoing = true;
}

GameInputCommand* EventHandler::getCommand(SDL_Event e) {
	if(this->commands.find(this->getKey(e)) == this->commands.end()) {
		return NULL;
	}
	return this->commands.find(this->getKey(e))->second;
}

EventHandler::~EventHandler() {
	std::map<string, GameInputCommand*>::iterator itr = this->commands.begin();
	while (itr != this->commands.end()) {
	   std::map<string, GameInputCommand*>::iterator toErase = itr;
	   delete toErase->second;
	   ++itr;
	}
	this->commands.clear();
}

void EventHandler::init() {

	//Comandos Viejos

	this->commands[this->getKey(SDL_KEYDOWN, SDLK_UP)] = new GameInputCommand(utils::KEY_PRESS_UP, "Press Up");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_LEFT)] = new GameInputCommand(utils::KEY_PRESS_LEFT, "Press Left");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_DOWN)] = new GameInputCommand(utils::KEY_PRESS_DOWN, "Press Down");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_RIGHT)] = new GameInputCommand(utils::KEY_PRESS_RIGHT, "Press Right");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_f)] = new GameInputCommand(utils::KEY_PRESS_JUMP, "Press Special Move");
		this->commands[this->getKey(SDL_KEYDOWN, SDLK_SPACE)] = new GameInputCommand(utils::KEY_PRESS_SHOOT, "Press Shoot");

	this->commands[this->getKey(SDL_KEYUP, SDLK_LEFT)] = new GameInputCommand(utils::KEY_RELEASE_LEFT, "Release Left");
	this->commands[this->getKey(SDL_KEYUP, SDLK_RIGHT)] = new GameInputCommand(utils::KEY_RELEASE_RIGHT, "Release Right");
	this->commands[this->getKey(SDL_KEYUP, SDLK_UP)] = new GameInputCommand(utils::KEY_RELEASE_UP, "Release Up");
	this->commands[this->getKey(SDL_KEYUP, SDLK_DOWN)] = new GameInputCommand(utils::KEY_RELEASE_DOWN, "Release Down");
	this->commands[this->getKey(SDL_KEYUP, SDLK_r)] = new GameInputCommand(utils::KEY_RELEASE_RELOAD, "Reload Game");

	//Comandos nuevos by Rodri

	this->commands[this->getKey(SDL_KEYDOWN, SDLK_w)] = new GameInputCommand(utils::KEY_PRESS_UP, "Press Up");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_a)] = new GameInputCommand(utils::KEY_PRESS_LEFT, "Press Left");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_s)] = new GameInputCommand(utils::KEY_PRESS_DOWN, "Press Down");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_d)] = new GameInputCommand(utils::KEY_PRESS_RIGHT, "Press Right");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_j)] = new GameInputCommand(utils::KEY_PRESS_JUMP, "Press Special Move");
	this->commands[this->getKey(SDL_KEYDOWN, SDLK_k)] = new GameInputCommand(utils::KEY_PRESS_SHOOT, "Press Shoot");

	this->commands[this->getKey(SDL_KEYUP, SDLK_a)] = new GameInputCommand(utils::KEY_RELEASE_LEFT, "Release Left");
	this->commands[this->getKey(SDL_KEYUP, SDLK_d)] = new GameInputCommand(utils::KEY_RELEASE_RIGHT, "Release Right");
	this->commands[this->getKey(SDL_KEYUP, SDLK_w)] = new GameInputCommand(utils::KEY_RELEASE_UP, "Release Up");
	this->commands[this->getKey(SDL_KEYUP, SDLK_s)] = new GameInputCommand(utils::KEY_RELEASE_DOWN, "Release Down");
	this->commands[this->getKey(SDL_KEYUP, SDLK_q)] = new GameInputCommand(utils::KEY_CYCLE_PREVIOUS, "Cycle Previous Weapon");
	this->commands[this->getKey(SDL_KEYUP, SDLK_e)] = new GameInputCommand(utils::KEY_CYCLE_NEXT, "Cycle Next Weapon");

}

string EventHandler::getKey(SDL_Event e) {
	return this->getKey(e.type, e.key.keysym.sym);
}

bool EventHandler::getKeepGoing() {
	return keepGoing;
}
void EventHandler::setGameReloader(GameReloader* reloader){
	this->gameReloader = reloader;
}
string EventHandler::getKey(Uint32 type, SDL_Keycode keyCode) {
	stringstream s;
	s << type << "|" << keyCode;
	return s.str();
}

void EventHandler:: stop(){
	Thread::stop();
}

void* EventHandler::process(){
	while(this->isRunning()){
		//Event handler
		SDL_Event e;
		while(SDL_PollEvent( &e )) {
			while(gameReloader->reload()){
				cout<<"Estoy esperando a que termine"<<endl;
				usleep(1000);
			}
			SDL_PumpEvents();
			SDL_FlushEvent(SDL_KEYDOWN);
			//User requests quit
			if( e.type == SDL_QUIT ) {
				this->keepGoing = false;
			} else {
				GameInputCommand* command = this->getCommand(e);
				if(command != NULL) {
					command->execute(client, server);
				}
			}
		}
	}
	return (void*)NULL;
}

} /* namespace client */
