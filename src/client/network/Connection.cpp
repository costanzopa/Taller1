/*
 * Connection.cpp
 *
 *  Created on: 17/09/2016
 *      Author: pablo
 */

#include "Connection.h"

namespace net {

Connection::Connection() {
	this->client = NULL;
	string log = "Connection";
	this->logger = new logger::Logger(log);
}

Connection::Connection(client::Client* client) {
	this->client = client;
	string log = "Connection";
	this->logger = new logger::Logger(log);
}
Connection::~Connection() {
	delete logger;
}

void* Connection::process() {
	try {
		while(this->isRunning()) {
			this->client->checkConnection();
		}
	} catch(exceptions::SocketException &e) {
		this->stop();
		std::cout<<std::endl;
		std::cout<<"ERROR::Se ha caido la conexión."<<std::endl;
		this->logger->error("Se ha caido la conexión");
		client->setDisconnect();
		return (void*) NULL;
	}
	return (void*) NULL;
}

} /* namespace net */
