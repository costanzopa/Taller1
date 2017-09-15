/*
 * ClientUI.h
 *
 *  Created on: Sep 5, 2016
 *      Author: mario
 */

#ifndef CLIENT_UI_CLIENTUI_H_
#define CLIENT_UI_CLIENTUI_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ClientUI {
public:
	ClientUI();
	virtual ~ClientUI();
	//void drawCharacterSelection();
	void drawLoginScreenUser();
	void drawLoginScreenPass();
	void drawMainMenu(vector<string> users);
	void drawSendMessageMenu();
	void drawSendMessage(const std::string& receiver);
	void drawReceiveMessage();
	void drawSelectReceiverMenu(vector<string> users);
	void drawLoremIpsumScreen();
	void drawErrorScreen(const std::string& message, const std::string& action);
	void drawInitialScreen();
	void printHeader(string title);
	void printFooter();

private:

	void clearScreen();

};

#endif /* CLIENT_UI_CLIENTUI_H_ */
