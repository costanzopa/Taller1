#include <iostream>
#include <string>
#include "User.h"
#include <cstring>
using namespace std;


User:: User(const std::string& user,const std::string& pass){
	this->userName = user;
	this->password = pass;
	connected = true;
}
void User::Disconnected(){
	connected = false;
}
void User::Connected(){
	connected = true;
}
bool User::isConnected(){
	return connected;
}
bool User :: isEqualTo(User* addresse){
	if(this->userName.compare(addresse->getUserName())== 0)
			return true;
	return false;
}

std::string& User:: getUserName(){
	return (this->userName);
}

std::string& User::getPassword() {
	return (this->password);
}

int User :: getNameSize(){
	return (int)this->userName.size();
}
User:: ~User(){
}
