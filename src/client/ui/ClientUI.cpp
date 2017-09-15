/*
 * ClientUI.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: mario
 */

#include "ClientUI.h"

ClientUI::ClientUI() {}

ClientUI::~ClientUI() {}

const string HEADER_SEPARATOR = "================================================================================";
const string FOOTER_SEPARATOR = "################################################################################";

const string MAIN_MENU_TITLE = "Menu Principal";
const string LOGIN_MENU_TITLE = "Login";
const string SEND_MESSAGE_TITLE = "Enviar Mensaje";
const string LOREN_IPSUM_MESSAGE_TITLE = "Lorem Ispum";
const string RECEIVE_MESSAGE = "Recibir Mensajes";
const string ERROR_SCREEN_TITLE = "ERROR";
const string CLIENT_SCREEN_TITLE = "Bienvenido!!!";



void ClientUI::drawLoginScreenUser() {
	this->clearScreen();
	this->printHeader(LOGIN_MENU_TITLE);
	cout << "Ingrese su nombre de Usuario" << endl;
	this->printFooter();
}

void ClientUI::drawLoginScreenPass() {
	this->clearScreen();
	this->printHeader(LOGIN_MENU_TITLE);
	cout << "Ingrese su password" << endl;
	this->printFooter();
}

void ClientUI::drawMainMenu(vector<string> users) {
	this->clearScreen();
	this->printHeader(MAIN_MENU_TITLE);
	cout << "Usuarios disponibles: ";
	for (std::vector<string>::iterator it = users.begin() ; it != users.end(); ++it) {
		cout <<" " << *it << endl;
	}
	cout << endl;
	cout << "Seleccione una opcion:" << endl;
	cout << endl;
	cout << "1 - Enviar Mensaje" << endl;
	cout << "2 - Recibir Mensajes" << endl;
	cout << "3 - Lorem Ipsum" << endl;
	cout << "4 - Iniciar Juego"<< endl;
	cout << "5 - Desconectarse" << endl;
	cout << "6 - Salir" << endl;
	this->printFooter();

}

void ClientUI::drawSendMessage(const std::string& receiver) {
	this->clearScreen();
	this->printHeader(SEND_MESSAGE_TITLE);
	cout << "Ingrese su Mensaje para " << receiver << endl;
	this->printFooter();
}

void ClientUI::drawReceiveMessage() {
	this->clearScreen();
	this->printHeader(RECEIVE_MESSAGE);
	cout << "Mensajes Recibidos" << endl;
}

void ClientUI::drawSelectReceiverMenu(vector<string> users) {
	this->clearScreen();
	this->printHeader(SEND_MESSAGE_TITLE);
	cout << "Seleccione un receptor:" << endl;
	cout << endl;
	int i = 1;
	for (std::vector<string>::iterator it = users.begin() ; it != users.end(); ++it) {
		cout << i <<" - " << *it << endl;
		i++;
	}
	cout << i <<" - " << "Todos" << endl;
	cout << (i + 1) <<" - " << "Volver" << endl;
	this->printFooter();
}

void ClientUI::drawLoremIpsumScreen() {
	this->clearScreen();
	this->printHeader(LOREN_IPSUM_MESSAGE_TITLE);
	cout << "Envia mensajes de forma aleatoria, en forma ciclica." << endl;
	this->printFooter();
}

void ClientUI::clearScreen() {
    //cout << string( 50, '\n' );
}

void ClientUI::drawErrorScreen(const std::string& message,const std::string& action) {
	this->clearScreen();
	this->printHeader(ERROR_SCREEN_TITLE);
	cout << message << endl;
	cout << endl;
	cout << action << endl;
	this->printFooter();
	string option = "";
	getline(cin, option);
}

void ClientUI::drawInitialScreen() {
	this->clearScreen();
	this->printHeader(CLIENT_SCREEN_TITLE);
	cout << "Seleccione una opcion:" << endl;
	cout << "1 - Sign In" << endl;
	cout << "2 - Salir" << endl;
	this->printFooter();
}

void ClientUI::printHeader(string title) {
	cout << HEADER_SEPARATOR << endl;
	cout << title << endl;
	cout << HEADER_SEPARATOR << endl;
	cout << endl;
}

void ClientUI::printFooter() {
	cout << endl;
	cout << FOOTER_SEPARATOR << endl;
	cout << endl;
}
