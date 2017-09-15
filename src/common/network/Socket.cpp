/*
 * Socket.cpp
 *
 *  Created on: 27/08/2016
 *      Author: pablo
 */

#include "Socket.h"
namespace net {

Socket::Socket() {
	this->init();
}

Socket::Socket(const std::string& port, const unsigned int connections) {
	this->init();
	this->startServer(port,connections);
}

Socket::Socket(const std::string& host, const std::string& port) {
	this->init();
	this->startClient(host,port);
}

Socket::~Socket() {
	this->close();
	delete logger;
}

void Socket::accept(Socket* newSocket) {
	 struct sockaddr_in cliSockAddr;
	 socklen_t cliSockAddrSize = sizeof (cliSockAddr);
	 int id = this->getSocketId();
	 int acceptError = ::accept(id, (struct sockaddr*) &cliSockAddr,
		    		&cliSockAddrSize);
	 if (acceptError >= VALID_RETURN) {
		newSocket->setSocketId(acceptError);
	 } else {
		 this->logger->error("Error al aceptar una conexion.");
		 throw exceptions::SocketException("ERROR al aceptar una conexion.");
	 }
}

void Socket::interrupt() {
	if (!this->wasInterrupted()) {
		this->setInterrupt(true);
		const int id = this->getSocketId();
		const int interrumpirError = ::shutdown(id, SHUT_RDWR);
		if (interrumpirError != VALID_RETURN) {
			this->logger->error("Error al interrumpir un socket.");
			throw exceptions::SocketException("ERROR al interrumpir un socket.");
		}
	}
}

void Socket::close() {
	if (socketInfo != NULL) {
		::freeaddrinfo(socketInfo);
		socketInfo = NULL;
    }
    socketInfoUsed = NULL;
    const int id = this->getSocketId();
    if (id != INVALID_SOCKET) {
    	try {
    		this->interrupt();
    	} catch (exceptions::SocketException &exception) {
    		const int closeError = ::close(id);
		    this->setSocketId(INVALID_SOCKET);
		    if (closeError != VALID_RETURN) {
				this->logger->error("Error en el cierre de un socket.");
		    	throw exceptions::SocketException("ERROR en el cierre de un socket.");
		    }
        }
	    const int closeError = ::close(id);
	    this->setSocketId(INVALID_SOCKET);
	    if (closeError != VALID_RETURN) {
			this->logger->error("Error en el cierre de un socket.");
		    throw exceptions::SocketException("ERROR en el cierre de un socket.");
        }
    }
}


ssize_t Socket::send(const void* buffer, const size_t bufferSize) const {
	   const int id = this->getSocketId();
	   errno = 0;
	   ssize_t sendBytes = ::send(id, buffer, bufferSize, ::MSG_NOSIGNAL);
	   if (sendBytes==-1) {
		   if ((errno==EBADF) || (errno==EPIPE)) {
			   sendBytes = 0;
		   } else {
			   this->logger->error("Error al enviar datos.");
			   throw exceptions::SocketException("Error al enviar datos.");
		   }
	   }
	   return sendBytes;
}

ssize_t Socket::receive(void* const buffer, const size_t bufferSize) const {
	const int id = this->getSocketId();
	struct timeval tv;
	tv.tv_sec = 10;  /* 5 Secs Timeout */
	tv.tv_usec = 0;  // Not init'ing this can cause strange errors
	setsockopt(id, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	errno = 0;
	ssize_t recvBytes = ::recv(id,buffer,bufferSize, 0);
	if((errno==EAGAIN)||(errno==EWOULDBLOCK)){
		printf("ERROR 1\n");
		this->logger->error("Error de conexion (Time out)");
		return 0;
	}
	if (recvBytes==-1) {
		printf("ERROR 2\n");
		if ((errno==EBADF) || (errno==EPIPE)) {
	 	    recvBytes = 0;
	 	} else {
				this->logger->error("Error al recibir bytes.");
	 		   throw exceptions::SocketException("ERROR al recibir bytes.");
	 	   }
	   }
	   return recvBytes;
}


void Socket::init() {
	 this->setInterrupt(false);
	 this->setSocketId(INVALID_SOCKET);
	 this->setSocketInfo(NULL);
	 this->setSocketInfoUsed(NULL);
	 std::string log = "Socket";
	 this->logger = new logger::Logger(log);
}

void Socket::init(struct addrinfo* const protocol) {
	::memset(protocol, 0, sizeof *protocol);
	protocol->ai_flags = (AI_V4MAPPED | AI_ADDRCONFIG);
	// Familia de direcciones IPv4 o IPv6.
	protocol->ai_family = AF_UNSPEC;
	// Tipo de socket STREAM.
	protocol->ai_socktype = SOCK_STREAM;
}

void Socket::startServer(const std::string& port, const unsigned int connections) {
	struct addrinfo protocol;
	init(&protocol);
	protocol.ai_flags |= AI_PASSIVE;

	int error = ::getaddrinfo(NULL, port.c_str(), &protocol, &socketInfo);

	if (error != VALID_RETURN) {
		this->logger->error("Error al generar el addrinfo.");
		throw exceptions::SocketException("Error al generar el addrinfo.");
	}
	for (socketInfoUsed = socketInfo; socketInfoUsed != NULL;
			socketInfoUsed = socketInfoUsed->ai_next) {
		try {
			this->config(connections);
		}catch (exceptions::SocketException &excepcion) {
			continue;
		}
		break;
	}
	if (socketInfoUsed == NULL) {
		::freeaddrinfo(socketInfo);
		socketInfo = NULL;
		this->logger->error("Error al conectar el socket Servidor.");
		std::string error("Error al conectar el socket Servidor.");
		throw exceptions::SocketException(error);
	}
}

void Socket::startClient(const std::string& host, const std::string& port) {
	struct addrinfo protocol;
	init(&protocol);
	protocol.ai_flags |= AI_PASSIVE;

	int error = ::getaddrinfo(host.c_str(), port.c_str(),
				&protocol, &socketInfo);

	if (error != VALID_RETURN) {
		this->logger->error("Error al generar el addrinfo.");
		throw exceptions::SocketException("Error al generar el addrinfo.");
	}
	for (socketInfoUsed = socketInfo; socketInfoUsed != NULL;
			socketInfoUsed = socketInfoUsed->ai_next) {
		try {
			this->config();
		}catch (exceptions::SocketException &exception) {
			continue;
		}
		break;
	}
	if (socketInfoUsed == NULL) {
		::freeaddrinfo(socketInfo);
		socketInfo = NULL;
		this->logger->error("Error al conectar el cliente.");
		throw exceptions::SocketException("Error al conectar el cliente.");
	}
}

void Socket::config(const int connections) {
	try {
		this->create();
		this->bind();
		this->listen(connections);
	} catch( exceptions::SocketException &exception) {
		int validId = this->getSocketId();
		if (validId != INVALID_SOCKET) {
			::close(validId);
			this->setSocketId(INVALID_SOCKET);
		}
		throw exception;
	}
}

void Socket::config() {
	try {
		this->create();
		this->connect();
	}catch(exceptions::SocketException& excepcion) {
		int idValido = this->getSocketId();
		if (idValido != INVALID_SOCKET) {
		    ::close(idValido);
			this->setSocketId(INVALID_SOCKET);
		}
		throw;
	}
}

void Socket::create() {
	int family = socketInfoUsed->ai_family;
	int type = socketInfoUsed->ai_socktype;
	int protocol = socketInfoUsed ->ai_protocol;
	socketId = socket(family, type, protocol);
	if (socketId < VALID_RETURN){
		this->logger->error("Error al crear el socket.");
		throw exceptions::SocketException("ERROR al crear el socket.");
	}
}

void Socket::bind() {
	int id = this->getSocketId();
	int yes = 1;
	const int opcionesError = ::setsockopt(id, SOL_SOCKET,
			SO_REUSEADDR, &yes, sizeof(int));
	    if (opcionesError != VALID_RETURN) {
			this->logger->error("Error en las opciones al bindear.");
	    	throw exceptions::SocketException("ERROR en las opciones al bindear.");
	    }
	    int error = ::bind(id, socketInfoUsed->ai_addr,
	    		socketInfoUsed->ai_addrlen);
	    if (error != VALID_RETURN) {
			this->logger->error("Error al realizar bind.");
			throw exceptions::SocketException("ERROR al realizar bind");
	    }
}

void Socket::listen(const int queue) {
	 int id = this->getSocketId();
	 const int listenError = ::listen(id, queue);
	 if (listenError != VALID_RETURN) {
		 this->logger->error("Error al escuchar una conexion.");
		 throw exceptions::SocketException("Error al escuchar una conexion.");
	 }
}

void Socket::connect() {
	int id = this->getSocketId();
	int error = 0;
	error = ::connect(id, socketInfoUsed->ai_addr,
			socketInfoUsed->ai_addrlen);
	if (error != VALID_RETURN) {
		this->logger->error("Error al conectar.");
	    throw exceptions::SocketException("ERROR al conectar.");
	}
}

// Getters y Setters

const int& Socket::getSocketId() const {
	return (this->socketId);
}

void Socket::setSocketId(const int socketId) {
	this->socketId = socketId;
}

const bool& Socket::wasInterrupted() const {
	return (this->interrupted);
}

void Socket::setInterrupt(const bool interrupted) {
	this->interrupted = interrupted;
}

void Socket::setSocketInfo(struct addrinfo* const socketInfo) {
	this->socketInfo = socketInfo;
}

void Socket::setSocketInfoUsed(struct addrinfo* const socketInfoUsado) {
	this->socketInfoUsed = socketInfoUsado;
}

}
