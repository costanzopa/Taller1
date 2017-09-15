#include <iostream>
#include "../../common/threads/Thread.h"
#include "../../estructurasDeDatos/DemandHandler.h"
#include "../../estructurasDeDatos/MessageList.h"

using namespace std;

class DemandAttendant: public threads::Thread{
	public:
	MessageList* messageList;
	DemandHandler* demandHandler;
	bool activated;
	public:
		DemandAttendant();
		virtual ~DemandAttendant();
		void setMessagesList(MessageList*);
		void setDemandHandler(DemandHandler*);
		virtual void stop();
	private:
		virtual void* process();
		
};
