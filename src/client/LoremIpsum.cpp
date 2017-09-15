/*
 * LoremIpsum.cpp
 *
 *  Created on: Sep 10, 2016
 *      Author: mario
 */

#include "LoremIpsum.h"

namespace lorem {

string ERROR_FILE = "El archivo indicado no existe o no se puede abrir.";
string INVALID_OPTION = "Opcion invalida. Intente nuevamente.";
int MAX_PKG_SIZE = 200;

LoremIpsum::LoremIpsum() {
	srand((unsigned)time(0));
	std::string loggerID = "LoremIpsum";
	logger = new Logger(loggerID);
	this->logger->setTrimMessage(true);
}

LoremIpsum::~LoremIpsum() {
	delete this->logger;
	/*if (this->connection != NULL) {
		delete connection;
	}*/
}

void LoremIpsum::run(vector<string> users, Client* client) {
	//this->startChecking(client);
	//this->client = client;

	float freq = this->readFrequency();
	int messages = this->readMessageNumber();
	string file = this->readFilePath();

	//this->stopChecking();

	//if (!client->isConnected())
	//	throw exceptions::SocketException("Error en el cliente");
	
	std::ifstream loremFile(file.c_str());
	if (!loremFile.good()) {
		this->logger->error(ERROR_FILE);
		cout << ERROR_FILE << endl;
		loremFile.close();
		return;
	}

	cout << endl;

	long wait = (long) (1000*1000 / freq);
	string usr = users.at(this->random(0, users.size() -1));
	int pkgSize = this->random(1, MAX_PKG_SIZE);
	int size = pkgSize;

	this->logger->debug("Cycle about to begin...");
	while (messages > 0) {
		string msg = "";
		bool readEnough = false;
		while (!readEnough) {
			char b[size + 1];
			loremFile.read(b, sizeof(b));
			string aux(b);
			msg = msg + aux;
			if (msg.size() < size) {
				loremFile.clear();
				loremFile.seekg(0, ios::beg);
				size = size - aux.size();
			} else {
				readEnough = true;
			}
		}

		if(!client->sendMessageToUser(msg, usr))
			this->logger->error("Send fail");

		usleep(wait);
		cout << "Mensaje enviado... " << endl;
		messages--;
		size = pkgSize;
	}
	this->logger->debug("... Cycle Ended.");
	loremFile.close();
}

int LoremIpsum::random(int min, int max) {
    return min + (rand() % (int)(max - min + 1));
}

float LoremIpsum::readFrequency() {
	string f;
	float freq;
	cout << "Ingrese la frequencia: ";
	while (true) {
		getline(cin, f);
		stringstream ss(f);
		//if (!client->isConnected()) {
		//	throw exceptions::SocketException("Error en el cliente");
		//}
		if (ss >> freq)
			break;
		cout << INVALID_OPTION << endl;
	}
	return freq;
}

int LoremIpsum::readMessageNumber() {
	string m;
	int messages;
	cout << "Ingrese el numero de mensajes: ";
	while (true) {
		getline(cin, m);
		stringstream ss(m);
		//if (!client->isConnected()) {
		//	throw exceptions::SocketException("Error en el cliente");
		//}
		if (ss >> messages)
			break;
		cout << INVALID_OPTION << endl;
	}
	return messages;
}

string LoremIpsum::readFilePath() {
	string inputfile;
	cout << "Ingrese el archivo de origen: ";
	getline(cin, inputfile);

	//if (!client->isConnected()) {
	//	throw exceptions::SocketException("Error en el cliente");
	//}

	string file;
	if (inputfile.empty()) {
		file = utils::DEFAULT_PATH_LOREM_FILE;
	} else {
		file = inputfile;
	}
	return file;
}

/*void LoremIpsum::stopChecking() {
	this->connection->stop();
	this->connection->close();
	delete this->connection;
	this->connection = NULL;
}

void LoremIpsum::startChecking(Client* client) {
	if (this->connection == NULL) {
		this->connection = new net::Connection(client);
		this->connection->start();
	}
}*/

} /* namespace lorem */
