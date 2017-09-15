#include "Node.h"
#include <iostream>
#include <list>
#include "MessageList.h"

using namespace std;

MessageList:: MessageList(){
		pthread_mutex_init(&mutex_lock,NULL);
		myList = new list<Node*>();
}

void MessageList:: addMesage(Node* message){
	this->lock_list();
	(myList)->push_back(message);
	this->unlock_list();
}
void MessageList::erraseMessagesFor(User* addressee){

	this->lock_list();
		if(myList->empty()){
			this->unlock_list();
			return;
		}
		list<Node*>:: iterator iter;
		iter = (myList)->begin();
		list<Node*>:: iterator iter2;
		bool message_not_found;
		do{
			message_not_found = true;
			if((*iter)->isMessageFor(addressee)){
				iter2 = iter;
				if(myList->size()==1){
					myList->erase(iter);
					break;
				}
				++iter2;
				myList->erase(iter);
				message_not_found = false;
				iter = iter2;
			}
			if(message_not_found)
				++(iter);
		}while((iter)!= myList->end());
		this->unlock_list();
}
/*La lista recibe un usuario y compara con los nodos que tiene a ver cuales
 * tienen como destinatario a este usuario, luego se pasan a otra lista, y se
 * devuelve la misma
 * */
list<Node*>* MessageList :: getMessagesFor(User* addressee){
	//cout<<myList->size()<<"			" <<addressee->getUserName() <<endl;
	list<Node*>* messagesForAddresse = new list<Node*>();
	//In case its empty we dont check for unread messages
	this->lock_list();
	if(myList->empty()){
		this->unlock_list();
		return messagesForAddresse;
	}
	list<Node*>:: iterator iter;
	iter = (myList)->begin();
	list<Node*>:: iterator iter2;
	bool message_not_found;
	do{
		message_not_found = true;
		if((*iter)->isMessageFor(addressee)){
			iter2 = iter;
			if(myList->size()==1){
				(messagesForAddresse)->push_back(*iter);
				myList->erase(iter);
				break;
			}
			++iter2;
			(messagesForAddresse)->push_back(*iter);
			myList->erase(iter);
			message_not_found = false;
			iter = iter2;
		}
		if(message_not_found)
			++(iter);
	}while((iter)!= myList->end());
	this->unlock_list();
	return messagesForAddresse;

}
bool MessageList:: isEmpty(){
	return myList->empty();
}
MessageList :: ~MessageList(){
	list< Node * >::iterator it = this->myList->begin();
	while (it != myList->end()) {
		delete (*it);
		it++;
	}
	delete myList;
}

