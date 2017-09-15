/*
 * ClientUIController.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: mario
 */

#include "ClientUIController.h"
#include "../network/Connection.h"
#include "../clientGameLogic/GameRefresher.h"
#include <stdio.h>
#include <string>

ClientUIController::ClientUIController(std::string& host, std::string& port) {
	std::string loggerID = "ClientUIController";
	logger = new Logger(loggerID);
	ui = new ClientUI();
	graphics = new Graphics(); ///nuevo
	client = new Client(host, port);
	quit = false;
	this->disconnect = false;
	this->port = port;
	this->host = host;
	lorem = new LoremIpsum();
	this->connection = NULL;
}

ClientUIController::~ClientUIController() {
	delete this->logger;
	delete this->ui;
	delete this->graphics;
	delete this->client;
	delete this->lorem;
	if (this->connection != NULL) {
		delete connection;
	}
}

int ClientUIController::startUI() {
	while(!quit) {
		this->ui->drawInitialScreen();
		int option = this->validateInputInNumericRange(1, 2 );
		if(option == 1) {
			try {
				if(this->login()) {
					this->disconnect = false;
					this->mainMenu();
				}
			} catch (exceptions::SocketException& e) {
				this->logger->error("Error inesperado de conexión.");
				this->ui->drawErrorScreen("Error inesperado de conexión", "Oprima una tecla para salir");
				quit = true;
			}
		} else {
			quit = true;
		}
	}
	return quit;
}

bool ClientUIController::login() {
	this->ui->drawLoginScreenUser();
	string usr;
	getline(cin, usr);
	this->ui->drawLoginScreenPass();
	string pass;
	getline(cin, pass);
	if(this->client->connect()) {
		if(this->client->login(usr, pass)) {
			return true;
		} else {
			this->ui->drawErrorScreen("Error al iniciar sesion", "Oprima una tecla para volver");
		}
	} else {
		this->ui->drawErrorScreen("Error al establecer la conexion", "Oprima una tecla para salir");
		quit = true;
	}
	logUser = usr;
	return false;
}

void ClientUIController::receiveMessages() {
	this->ui->drawReceiveMessage();
	this->client->printMessages();
	this->ui->printFooter();
	cout << "Oprima una tecla para volver" << endl;
	string option;
	getline(cin, option);
}

void ClientUIController::sendMessage(string& receiver, string mode) {
	this->ui->drawSendMessage(receiver);
	this->startChecking();
	std::string message;
	getline(cin,message);
	this->stopChecking();
	bool success = this->client->sendMessage(receiver, mode, message);
	if(!success) {
		this->ui->drawErrorScreen("Error Inesperado", "Oprima una tecla para salir");
		this->quit = true;
	}
}

void ClientUIController::sendMessageToAll() {
	this->ui->drawSendMessage("Todos");
	std::string message;
	this->startChecking();
	getline(cin, message);
	this->stopChecking();
	vector<string> usrs = this->client->retreiveAllUsers();
	for (std::vector<string>::iterator it = usrs.begin() ; it != usrs.end(); ++it) {
		bool success = this->client->sendMessageToUser(message, *it);
	}
}

string ClientUIController::selectReceiver(vector<string> users) {
	int usrNbr = users.size();
	cout << "nbr " << usrNbr << endl;
	this->ui->drawSelectReceiverMenu(users);
	int option = this->validateInputInNumericRangeConnected(1, usrNbr +2,usrNbr);
	if(option == usrNbr + 1) {
		return utils::ALL_USERS;
	}
	if(option == usrNbr +2) {
		return "";
	}
	return users.at(option - 1);
}

void ClientUIController::mainMenu() {
	bool loop = true;
	while(loop) {
		this->ui->drawMainMenu(this->client->retreiveAllUsers());
		int option = this->validateInputInNumericRange(1, 5);
		if (!this->isConnected()) {
				quit = true;
				loop = false;
				break;
		}
		if(option == 1) {
			string receiver = this->selectReceiver(this->client->retreiveAllUsers());
			if (this->isConnected()) {
				if(!receiver.empty()) {
					if(receiver.compare(utils::ALL_USERS) != 0)
						this->sendMessage(receiver, utils::SINGLE_MESSAGE);
					else
						this->sendMessageToAll();
				}
			} else {
				quit = true;
				loop = false;
			}
		}
		/*if(option == 1) {
			string receiver = this->selectReceiver(this->client->retreiveAllUsers());
			if(!receiver.empty()) {
				if(receiver.compare(utils::ALL_USERS) != 0)
					this->sendMessage(receiver, utils::SINGLE_MESSAGE);
				else
					this->sendMessageToAll();
				}
			 else {
				quit = true;
				loop = false;
			}
		}*/
		if(option == 2) {
			this->receiveMessages();
		}
		if(option == 3) {
			this->sendMessageLoremIpsum();
		}
		if(option == 4){
			this->startGame();
		}
		if(option == 5) {
			this->client->disconnect();
			loop = false;
			this->disconnect = true;
		}
		if(option == 6) {
			if (this->disconnect == false) {
				this->client->disconnect();
			}
			quit = true;
			loop = false;
		}
	}
}

int ClientUIController::validateInputInNumericRange(int since, int to) {
	string input;
	int option;
	this->startChecking();
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if ((ss >> option && option >= since && option <= to))
		   break;

		cout << "Opcion invalida. Intente nuevamente." << endl;
	}
	this->stopChecking();
	return option;
}

int ClientUIController::validateInputInNumericRangeConnected(int since, int to, int error) {
	string input;
	int option;
	this->startChecking();
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (!this->isConnected()) {
			option = error;
			break;
		}
		if ((ss >> option && option >= since && option <= to))
		   break;

		cout << "Opcion invalida. Intente nuevamente." << endl;
	}
	this->stopChecking();
	return option;
}  //Master

void ClientUIController::sendMessageLoremIpsum() {
	this->ui->drawLoremIpsumScreen();
	this->lorem->run(this->client->retreiveAllUsers(), client);
	cout << "Lorem Ipsum Finalizado. Oprima una tecla para continuar";
	string option = "";
	getline(cin, option);
}

void ClientUIController::stopChecking() {
	this->connection->stop();
	this->connection->close();
	delete this->connection;
	this->connection = NULL;
}

void ClientUIController::startChecking() {
	if (this->connection == NULL) {
		this->connection = new Connection(this->client);
		this->connection->start();
	}
}

bool ClientUIController::isConnected() {
	if (client != NULL) {
		return client->isConnected();
	} else {
		return false;
	}
}  //Master

void ClientUIController:: startGame(){
	if(this->client->startGame())
		this->graphics->loopGame(this->client);
	printf("La partida esta esta llena\n");

}
