/*
 * GameInputCommand.cpp
 *
 *  Created on: Oct 10, 2016
 *      Author: mario
 */

#include "GameInputCommand.h"

GameInputCommand::GameInputCommand(const std::string& msg, const std::string& action) {
	message.append(utils::EXISTING_CHARACTER);
	message.append("|");
	message.append(msg);
	performedAction = action;
}

GameInputCommand::~GameInputCommand() {}

void GameInputCommand::execute(Client* client, std::string server) {
	//cout<<"We will send this message"<<endl;
	client->sendMessageToUser(message,server);
	//cout << performedAction <<endl;
}
