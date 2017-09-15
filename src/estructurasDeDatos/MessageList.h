/*
 * List.h
 *
 *  Created on: 02/09/2016
 *      Author: guido
 */
#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include "Node.h"
#include <list>
#include <pthread.h>
using namespace std;
/*La clase messageList contiene todos los mensajes para todos los usuario
 * La lista contiene nodos que se conforman por Origen, Destinatario y Mensaje
 * */

class MessageList{
	list<Node*>* myList;
	pthread_mutex_t mutex_lock;
	public:
		MessageList();
		void addMesage(Node*);
		bool isEmpty();
		list<Node*>* getMessagesFor(User*);
		void erraseMessagesFor(User*);
		~MessageList();
	private:
		void lock_list(){ pthread_mutex_lock(&mutex_lock);}
		void unlock_list(){ pthread_mutex_unlock(&mutex_lock);}

};

#endif /* LIST_H_ */
