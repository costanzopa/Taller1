/*
 * Client.h
 *
 *  Created on: 01/09/2016
 *      Author: pablo
 */

#ifndef SRC_CLIENT_CLIENT_H_
#define SRC_CLIENT_CLIENT_H_

#include "../common/network/Communication.h"
#include "../common/utils/Constants.h"
#include "../common/logger/Logger.h"
#include "../estructurasDeDatos/Node.h"
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>
#include <pthread.h>

namespace client {

class Client {
public:
	net::Communication* communication;
	Client();
	Client(std::string& host, std::string& port);
	virtual ~Client();
	bool connect();
	void disconnect();
	const std::string& getAllMessages();
	void setQuit();
	bool getQuit();
	string getScales();
	bool sendMessageToUser(std::string& message, std::string& to);
	bool sendMessage(std::string& to, std::string mode);
	bool sendMessage(std::string& to, std::string mode,std::string& message);
	void cycle();
	void printMessages();
	void printHelp();
	void process();
	void quitGame();
	bool& isConnected(); //Master
	void setDisconnect(); //Master
	void checkConnection();//Master
	string getUser();

	bool startGame();
	list<Node*>* getMessages();

	bool login(std::string userName, std::string password);
	std::vector<std::string> retreiveAllUsers();
	bool getGameReady();
private:
	//Metodos Privados
	int validateInputInNumericRange(int since, int to);
	void getAllUsers();
	void printAllUsers();
	void setAllUsers(std::string& allUsers);
	void lock_client(){ pthread_mutex_lock(&mutex_lock);}
	void unlock_client(){ pthread_mutex_unlock(&mutex_lock);}
	//Atributos
	pthread_mutex_t mutex_lock;

	std::vector<std::string> users;
	std::string host;
	std::string port;
	bool quit;
	std::string user;
	std::string message;
	logger::Logger* logger;
	bool connected; //Master
};

} /* namespace client */

#endif /* SRC_CLIENT_CLIENT_H_ */
