#include "../includes/Client.hpp"

//so weird so random
int Client::_globalId;


//*CONSTRUCTORS
Client::Client(int srvSocket){
	_id = _globalId++;
	_socket = srvSocket;
	_pfd.fd = _socket;
	_pfd.events = POLLIN;
	_pfd.revents = 0;
}


//*GETTERS
int		Client::getId() {
	return (_id);
}

int		Client::getSocket() {
	return (_socket);
}

pollfd	&Client::getPfd() {
	return (_pfd);
}