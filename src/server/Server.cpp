/*
 * Server.cpp
 *
 *  Created on: 30/08/2016
 *      Author: pablo
 */

#include "Server.h"
#define ESCALA_JUGADOR 1.0

namespace server {


Server::Server():serverSocket(utils::DEFAULT_PORT,utils::MAX_QUEUE) {
	this->usersPath = utils::DEFAULT_PATH_USER_FILE;
	setServer();
}

Server::Server(const std::string& port, const int queue,const std::string& usersPath)
			  :serverSocket(port,queue) {
			  	this->usersPath = usersPath;
			  	setServer();
}
void Server::setServer(){
	this->messageList = new MessageList();
	this->gameList = new MessageList();
	this->userIdProvider = new UserIdProvider();
  	config::StageFile stageFile(utils::STAGE_FILE);
  	stage = stageFile.getStage();
  	if (stage != NULL) {
  		this->game = new GameManager(messageList,gameList,stage);
  	} else {
  		this->game = new GameManager(messageList,gameList,ESCALA_JUGADOR);
  	}
	string log = "Server";
	this->logger = new Logger(log);
	logger->info("Se conecta el server");
}

Server::~Server() {
	std::vector< UserConnection * >::iterator it = this->connections.begin();
	while (it != connections.end()) {
		(*it)->close();
		delete (*it);
		it++;
	}
	delete this->messageList;
	delete this->userIdProvider;
	delete this->logger;
}

void* Server::process() {
	cout<<"Hello"<<endl;
	this->game->start();
	net::Communication* clientSocket = NULL;
	try {
		while(this->isRunning()) {
			clientSocket = new net::Communication();
			this->serverSocket.accept(clientSocket);
			User* login = clientSocket->receiveUser();
			if (this->userIdProvider->validateUser(login->getUserName(),login->getPassword())) {
				clientSocket->sendString(utils::OK_MESSAGE);
				UserConnection* request = new UserConnection(this->messageList,login, clientSocket,this->userIdProvider->getAllUsers(),this->gameList);
				request->addGameManager(game);
				//request->setGameScales(stage->getWindow()->getWindowScale(),stage->getWindow()->getCharacterScale());
				logger->info("Se conecto a el server: " + login->getUserName());
				this->connections.push_back(request);
				request->start();
			} else {
				clientSocket->sendString(utils::ERROR_MESSAGE);
				logger->error("No se pudo conectar Login inválido" + login->getUserName());
				clientSocket->interrupt();
				delete clientSocket;
			}
		}
	} catch(std::exception  &e) {
		logger->info("Se ha cerrado el servidor");
		if (clientSocket!=NULL) {
			delete clientSocket;
			game->stop();
			delete game;
		}
		return (void*) NULL;
	}
	return (void*) NULL;
}

void Server::stop() {
	this->serverSocket.interrupt();
	logger->info("Se desconecta el server");
}

} /* namespace server */
