/*
 * UserProvider.h
 *
 *  Created on: Sep 4, 2016
 *      Author: mario
 */

#ifndef COMMON_USERIDPROVIDER_H_
#define COMMON_USERIDPROVIDER_H_

#include "utils/Tokenizer.h"
#include "logger/Logger.h"


#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <exception>

using namespace std;
using namespace logger;

class UserIdProvider {
public:
	UserIdProvider();
	virtual ~UserIdProvider();

	vector<string>& getAllUsers();
	bool validateUser(std::string& usr, std::string& pass);

private:
	map<string, string> validUsers;
	vector<string> users;
	void init(std::string& file);
	Logger* logger;

};

#endif /* COMMON_USERIDPROVIDER_H_ */
