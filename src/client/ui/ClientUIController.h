/*
 * ClientUIController.h
 *
 *  Created on: Sep 5, 2016
 *      Author: mario
 */

#ifndef CLIENT_UI_CLIENTUICONTROLLER_H_
#define CLIENT_UI_CLIENTUICONTROLLER_H_

#include <iostream>
#include <string>
#include <sstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ClientUI.h"
#include "../../common/logger/Logger.h"
#include "../Client.h"
#include "../network/Connection.h"

#include "../LoremIpsum.h"
#include "../../estructurasDeDatos/ClientGameStatus.h"
#include "../clientGameLogic/Graphics.h"

using namespace std;
using namespace logger;
using namespace client;
using namespace lorem;
using namespace net;

class ClientUIController {
public:
	ClientUIController(std::string& host, std::string& port);
	virtual ~ClientUIController();

	int startUI();

private:
	string logUser;
	ClientUI* ui;
	Graphics* graphics;
	Logger* logger;
	Client* client;
	Connection* connection;
	string port;
	string host;



	bool quit;
	bool disconnect;
	LoremIpsum* lorem;
	void startGame();
	void loopGame();
	bool login();
	void mainMenu();
	void receiveMessages();
	void sendMessage(string& receiver, string mode);
	void sendMessageToAll();
	void sendMessageLoremIpsum();
	string selectReceiver(vector<string> users);
	int validateInputInNumericRange(int since, int to);
	int validateInputInNumericRangeConnected(int since, int to, int error);
	void startChecking();
	void stopChecking();
	bool isConnected();

};

#endif /* CLIENT_UI_CLIENTUICONTROLLER_H_ */
