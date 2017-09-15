/*
 * GameInputCommand.h
 *
 *  Created on: Oct 10, 2016
 *      Author: mario
 */

#ifndef CLIENT_CLIENTGAMELOGIC_GAMEINPUTCOMMAND_H_
#define CLIENT_CLIENTGAMELOGIC_GAMEINPUTCOMMAND_H_

#include <string>
#include "../Client.h"

using namespace std;
using namespace client;


class GameInputCommand {
public:
	GameInputCommand(const std::string& message, const std::string& action);
	virtual ~GameInputCommand();

	void execute(Client* client, std::string server);

private:
	std::string message;
	std::string performedAction;
};

#endif /* CLIENT_CLIENTGAMELOGIC_GAMEINPUTCOMMAND_H_ */
