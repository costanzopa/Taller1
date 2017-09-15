#ifndef OUTCOMINGMESSAGES_H_
#define OUTCOMINGMESSAGES_H_

#include <iostream>
#include "Node.h"
#include <queue>
#include <list>
#include <pthread.h>
using namespace std;

/*Esta es la cola donde se ponen los mensajes que seran sacados por el
 * message sender que los enviara a travez del socket al cliente
 *
 * */
class OutcomingMessages{
	pthread_mutex_t queue_mutex;
	queue<list<Node*>*>* messages;
	public:
		OutcomingMessages();
		virtual ~OutcomingMessages();
		void pushMessage(list<Node*>* message);
		list<Node*>* popMessage();
		void lockQueue(){ pthread_mutex_lock(&queue_mutex);}
		void unlockQueue(){pthread_mutex_unlock(&queue_mutex);}
		bool isEmpty(){ return messages->empty(); }

};
#endif
