/*
 * Node.h
 *
 *  Created on: 02/09/2016
 *      Author: guido
 */

#ifndef NODE_H_
#define NODE_H_

#include "User.h"
/*Node es el nodo que se guarda en la lista de mensajes
 * Tiene un origen, un destino, y el mensaje
 * Los atributos message_size y buffer_position, son utilizados para la
 * parte de envio de mensajes a travez de sockets
 * */

class Node{
	User* destination;
	User* origin;
	string message;
	bool read;
	int message_size;
	int buffer_position;

	public:
		Node(User*,User*,std::string&);
		std::string& Read();
		bool wasRead();
		bool isMessageFor(User*);
		char* getOrigin();
		char* getMessage(int buffer);
		int getBuffSize(int max_buff_size);
		const unsigned int getBuffSize() const;
		const std::string& getMessage() const;
		User* getFrom();
		User* getTo();
		int getUserNameSize();
		bool messageWasTransfered(){ return buffer_position == message_size; }
		virtual ~Node();

};


#endif /* NODE_H_ */
