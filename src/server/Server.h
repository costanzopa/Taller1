/*
 * Server.h
 *
 *  Created on: 30/08/2016
 *      Author: pablo
 */

#ifndef SRC_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_H_

#include "../common/network/Communication.h"
#include "conexion/UserConnection.h"
#include "../common/utils/Constants.h"
#include "../common/threads/Thread.h"
#include "../common/logger/Logger.h"
#include "../common/UserIdProvider.h"
#include "logicaDelServidor/GameRelated/GameManager.h"
#include "config/stage/StageFile.h"
#include "config/stage/Stage.h"

namespace server {

class Server: public threads::Thread {
	public:
		Server();
		Server(const std::string& port, const int queue, const std::string& usersPath);
		virtual ~Server();
		virtual void stop();
		const bool isValidUser(User* login) const;

		//Metodos privados
	private:
		virtual void* process();
		Server(const Server &Server);
		Server& operator=(const Server &server);
		void setServer();

		//Miembros de la clase
		GameManager* game;
		std::vector<UserConnection*> connections;
		net::Communication serverSocket;
		std::string usersPath;
		MessageList* messageList;
		MessageList* gameList;
		UserIdProvider* userIdProvider;
		Logger* logger;
		config::Stage* stage;
};
} /* namespace server */

#endif /* SRC_SERVER_SERVER_H_ */
