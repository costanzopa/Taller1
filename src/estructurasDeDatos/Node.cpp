#include <iostream>
#include "Node.h"

#include<cstring>
using namespace std;



Node :: Node(User* from,User* to,std::string& text){
	destination = to;
	origin = from;
	message = text;
	message_size = (int) message.size();
	buffer_position = 0;
	read = false;
}

std::string& Node :: Read(){
	read = true;
	return message;
}

bool Node :: wasRead(){
	return read;
}
bool Node:: isMessageFor(User* addresse){
	return destination->isEqualTo(addresse);
}
Node:: ~Node(){
	delete destination;
	delete origin;
}



/*Devuelve un puntero al mensaje en la posicion en que se encuentra el
 * buffer position, luego le suma al buffer position, el buffer size para
 * saber en donde se quedo leyendo y de ahi continuar la proxima vez
 * */
char* Node :: getMessage(int bufsize){
	char* message_to_read = ((char*)message.c_str()+buffer_position);
	buffer_position += bufsize;
	return message_to_read;
}

/*Se le envia una cantidad "tentativa" de caracteres que se desea leer 
 * y devuelve la cantidad de caracteres que se puede llegar a leer dependiendo
 * cuantos son los que faltan para terminar el mensaje 
 * */
int Node :: getBuffSize(int max_buff_size){
	int left_over_message = message_size - buffer_position;
	if(max_buff_size > left_over_message)
		return left_over_message;
	return max_buff_size;
}
int Node :: getUserNameSize(){
	return origin->getNameSize();
}

const unsigned int Node::getBuffSize() const {
	return (message.size());
}

const std::string& Node::getMessage() const {
	return this->message;
}

User* Node::getFrom(){
	return this->origin;
}

User* Node::getTo() {
	return this->destination;
}
