/*
 * LoremIpsum.h
 *
 *  Created on: Sep 10, 2016
 *      Author: mario
 */

#ifndef CLIENT_LOREMIPSUM_LOREMIPSUM_H_
#define CLIENT_LOREMIPSUM_LOREMIPSUM_H_

#include "../common/logger/Logger.h"
#include "Client.h"
#include "network/Connection.h"


#include <string>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;
using namespace logger;
using namespace client;


namespace lorem {

class LoremIpsum {
public:
	LoremIpsum();
	virtual ~LoremIpsum();

	void run(vector<string> users, Client* client);
	int random(int min, int max);

private:
	Logger* logger;
	float readFrequency();
	int readMessageNumber();
	string readFilePath();
	//void startChecking(Client* client);
	//void stopChecking();
	net::Connection* connection;
	Client* client;
};

} /* namespace lorem */

#endif /* CLIENT_LOREMIPSUM_LOREMIPSUM_H_ */
