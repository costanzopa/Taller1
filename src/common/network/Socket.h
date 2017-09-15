/*
 * Socket.h
 *
 *  Created on: 27/08/2016
 *      Author: pablo
 */

#ifndef SRC_COMMON_NETWORK_SOCKET_H_
#define SRC_COMMON_NETWORK_SOCKET_H_

#include <string>
#include <iostream>
#include <cstddef>
#include <sys/socket.h>
#include <netdb.h>  /* Struct "addrinfo". */
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#include "../utils/Exception.h"
#include "../logger/Logger.h"

#define INVALID_SOCKET -1
#define VALID_RETURN 0

namespace net {
class Socket {
public:

	Socket();

	/**
	 * Intenta crear y abrir un socket en modo server
	 */
	Socket(const std::string& port, const unsigned int connections);

	/**
	 * Intenta crear y abrir un socket en modo client
	 */
	Socket(const std::string& host, const std::string& port);

	/**
	 * Libera los recursos y cierra el socket
	 */
	virtual ~Socket();

	void accept(Socket* newSocket);

	void interrupt();

	void close();


	ssize_t send(const void* buffer, const size_t bufferSize) const;
	ssize_t receive(void* const buffer, const size_t bufferSize) const;

private:
	Socket(const Socket& socket);
	Socket& operator=(const Socket& socket);

	void init();
	void init(struct addrinfo* const protocol);
	void startServer(const std::string& port, const unsigned int connections);
	void startClient(const std::string& host, const std::string& port);

	void create();
	void bind();
	void config(const int connections);
	void config();
	void listen(const int queue);
	void connect();

	//Setters y getters
	const bool& wasInterrupted() const;
	void setInterrupt(const bool interrupt);
	void setSocketId(const int socketId);
	void setSocketInfo(struct addrinfo* const socketInfo);
	void setSocketInfoUsed(struct addrinfo* const socketInfoUsed);
	const int& getSocketId() const;


	int socketId;
	struct addrinfo* socketInfo;
	struct addrinfo* socketInfoUsed;
	bool interrupted;
	logger::Logger* logger;

};
}

#endif /* SRC_COMMON_SOCKET_H_ */
