/*
 * UserProvider.cpp
 *
 *  Created on: Sep 4, 2016
 *      Author: mario
 */

#include "UserIdProvider.h"

#include "utils/Tokenizer.h"


#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;


UserIdProvider::UserIdProvider() {
	std::string defaultFile = "../users.txt";
	std::string loggerID = "UserIdProvider";
	logger = new Logger(loggerID);
	this->init(defaultFile);
}

UserIdProvider::~UserIdProvider() {
	delete logger;
}

vector<string>& UserIdProvider::getAllUsers() {
	return this->users;
}

bool UserIdProvider::validateUser(std::string& usr, std::string& pass) {
	return ((this->validUsers.find(usr) != this->validUsers.end())
			&& (this->validUsers.find(usr)->second == pass));
}

void UserIdProvider::init(std::string& file) {
	std::ifstream usrFile(file.c_str());
	if(!usrFile.good()){
		this->logger->error("Users configuration file not found or with errors");
		throw exception();
		return;
	}
	Tokenizer* tkn = new Tokenizer();
	int i = 1;
	for( string line; getline( usrFile, line ); ) {
		stringstream s;
		vector<string> tkns = tkn->tokenize(line, '|');
		if(tkns.size() != 2) {
			s << "Invalid amount of fields. Expected <user>|<pass>. Line: " << i;
		} else {
			if(this->validUsers.find(tkns[0]) == this->validUsers.end()) {
				this->validUsers[tkns[0]] = tkns[1];
				this->users.push_back(tkns[0]);
				s << "User added. Line: " << i;
			} else {
				s << "Duplicate user, line: " << i;
			}
		}
		this->logger->info(s.str());
		i++;
	}
	delete tkn;
	usrFile.close();
}
