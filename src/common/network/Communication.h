/*
 * Communication.h
 *
 *  Created on: 28/08/2016
 *      Author: pablo
 */

#ifndef SRC_COMMON_NETWORK_COMMUNICATION_H_
#define SRC_COMMON_NETWORK_COMMUNICATION_H_

#include "Socket.h"
#include "../../estructurasDeDatos/User.h"
#include "../../estructurasDeDatos/Node.h"
#include "../logger/Logger.h"
#include "../utils/Constants.h"
#include <sstream>

#define BUFFERSIZE 1024


namespace net {

class Communication {
public:
	Communication();
	/**
	 * El constructor utilizado para iniciar el servidor.
	 * @param port puerto en el cual se conecta el servidor
	 * @param queue La cantidad de conexiones disponibles a esperar
	 * en el connect.
	 */
	Communication(const std::string &port, const int queue);
	/**
	 * El constructor utilizado para iniciar al cliente.
	 * @param host Host al cual se conestara el servidor
	 * @param port Puerto utilizado para conectarse al servidor
	 */
	Communication(const std::string &host, const std::string &port);
	/**
	 *
	 * @param Metodo perteneciente al server para aceptar una comunicacion nueva
	 */
	 void accept(Communication* communication);

	 /**
	  * Destructor
	 */
	 virtual ~Communication();

	 //Interrumpir la comunicacion
	 void interrupt();


	 void setInActive();

	 bool& getActive();

	 /**
	  * Metodos de recepcion y envio de mensajes de tipo texto.
	  * Corte por fin largo del string
	  */
	 void sendString(const std::string &message) const;
	 void receiveString(std::string& message) const;

	 /**
	  * Envio y recepcion de un usuario para la verificacion del login
	  */
	 virtual void sendUser(User* user);
     virtual void sendUser(std::string& username, std::string& password);
	 virtual User* receiveUser();
	 
	 /**
	  * Metodos de recepcion y envio de un mensaje simple para almacenar en el servidor.
	  */
	 virtual void sendMessage(std::string& from, std::string& to, std::string& message);
  	 virtual Node* receiveMessage();

  	 /**
	  * Metodos de recepcion y envio de un nodo.
	  */
  	 virtual void sendNode(Node* message);
  	 virtual Node* receiveNode();

private:
	const Socket& getSocket() const;
	Socket* socket;
	std::string pendingMessage;
	logger::Logger* logger;
	bool active;
};

} /* namespace net */

#endif /* SRC_COMMON_NETWORK_COMMUNICATION_H_ */
