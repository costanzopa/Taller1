/*
 * Connection.h
 *
 *  Created on: 17/09/2016
 *      Author: pablo
 */

#ifndef CLIENT_NETWORK_CONNECTION_H_
#define CLIENT_NETWORK_CONNECTION_H_

#include "../Client.h"
#include "../../common/logger/Logger.h"
#include "../../common/threads/Thread.h"
#include "../../common/utils/Constants.h"

namespace net {

class Connection: public threads::Thread {
public:
	Connection();
	Connection(client::Client* client);
	virtual ~Connection();

private:
	virtual void* process();
	Connection(const Connection &connection);

	logger::Logger* logger;
	client::Client* client;
};

} /* namespace net */

#endif /* CLIENT_NETWORK_CONNECTION_H_ */
