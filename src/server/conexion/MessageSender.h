#include "../../estructurasDeDatos/OutcomingMessages.h"
#include <iostream>
#include "../../common/threads/Thread.h"
#include "../../common/network/Communication.h"
#ifndef MESSAGESENDER_H_
#define MESSAGESENDER_H_
using namespace std;

class MessageSender : public threads::Thread{
	OutcomingMessages* messages_for_user;
	net::Communication* communication;
	Node* end_of_stream_node;
	bool activated;
	public:
		MessageSender();
		virtual ~MessageSender();
		void setMessageQueue(OutcomingMessages* messages);
		void setCommunication(net::Communication*);
		void execute(void*);
		virtual void stop();
	private:
		virtual void* process();

};
#endif
