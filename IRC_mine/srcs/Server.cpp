#include "../includes/Server.hpp"


//*CONSTRUCTORS
Server::Server(char *port, char *pass){
	_port = atoi(port);
	_pass = pass;

	_socket = mySocket(AF_INET, SOCK_STREAM, 0);

	int opt = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_port);
	inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);//check "0.0.0.0"

	myBind(_socket, (sockaddr*)&server_addr, sizeof(server_addr));

	myListen(_socket, SOMAXCONN);

	std::cout << "Server open in port: " << _port << std::endl;
	// std::cout << GREEN("Server open in port: ") << _port << std::endl;

	_srvPfd.fd = _socket;
	_srvPfd.events = POLLIN;
	_srvPfd.revents = 0;
}


//*GETTERS
int			Server::getSocket() { return (_socket); }
int			Server::getPort() { return (_port); }
std::string Server::getPass() { return (_pass); }


//*Accepting client
int		Server::acceptClient()
{
	int			tempSocket;
	sockaddr_in	clientAddr;
	socklen_t	clientSize = sizeof(clientAddr);
	char		host[NI_MAXHOST];
	
	tempSocket = accept(_socket, (sockaddr*)&clientAddr, &clientSize);
	if (tempSocket == -1)
		throw (std::runtime_error("Problem with client connecting"));
	memset(host, 0, NI_MAXHOST);//useless?
	
	inet_ntop(AF_INET, &clientAddr.sin_addr, host, NI_MAXHOST);
	std::cout << host << " manually connected on " << ntohs(clientAddr.sin_port) << std::endl;
	return (tempSocket);
}

//*Set pollfds for loop
void	Server::setPfds()
{
	_pfds.clear();
	_pfds.push_back(_srvPfd);
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		_pfds.push_back(it->getPfd());
}

//*Disconnect client when client exits
void	Server::disconnectClient(Client client, int i)
{
	std::cout << "Client " << client.getId() << " disconnected" << std::endl;

	close (_pfds[i].fd);
	_clients.erase(_clients.begin() + i - 1);
}

//this is just testing
bool	Server::shouldServerExit(char buf[])
{
	if (strncmp(buf, "exit", 4) == 0) {
		std::cout << "exiting server" << std::endl;
		for (std::vector<Client>::iterator client_it = _clients.begin(); client_it != _clients.end(); client_it++)
			close(client_it->getSocket());
		close(_socket);
		return (true);
	}
	return (false);
}


//debug message
void	debugClientMessage(Client client, char buf[])
{
	std::cout << "Client " << client.getId() << " said: " << buf;
}	


enum	pollCondition//fucking stupid find a better solution
{
	DISCONNECT,
	EXIT,
	OK
};

int	Server::handleClientPoll(int i)
{
	char buf[512];//this can change for a vector if needed
	int bytesRecv = myRecv(_pfds[i].fd, buf, sizeof(buf), 0);
	if (bytesRecv == 0) {
		disconnectClient(_clients[i - 1], i);//sending index like this feels stupid
		return (DISCONNECT);
	}
	buf[bytesRecv] = 0;
	debugClientMessage(_clients[i - 1], buf);//the i - 1 is stupid

	if (shouldServerExit(buf))
		return (EXIT);

	// !processCommand(clients[i - 1], buf);
	return (OK);
}


void	Server::srvRun()
{
	while (1)
	{
		setPfds();

		myPoll(_pfds.data(), _pfds.size(), -1);

		if (_pfds[0].revents & POLLIN){
			int temp = acceptClient();
			_clients.push_back(Client(temp));
		}//* Client Connecting
	
		for (int i = 1; i < _pfds.size(); i++)//*loop through clients
		{
			if (_pfds[i].revents & POLLIN) {
				int ret = handleClientPoll(i);
				if (ret == DISCONNECT)//i dont like this
					continue ;
				else if (ret == EXIT)
					return ;
			}
		}
	}
	close(_socket);
}




/* 
// ! send ERR_PASSWDMISMATCH (464)
	send(clients[i - 1].getSocket(), "Client closing", 15, 0);//!send the err instead of this
	close (pfds[i].fd);
	clients.erase(clients.begin() + (i - 1));
enum Command//use this???
{
	EXIT,
	PASS,
	QUIT,
};

int	getCommand(char buf[])//use this?
{
	//strcmp for values?
	if (!strcmp(buf, pass))//should be in class already to process this?
		return PASS;
	return (-1);
}

//everything is a specific command
void	processCommand(Client client, char line[])
{
	int command = getCommand(line);
	switch (command)//use this??
	{
		case PASS:
			std::cout << "Pass command found" << std::endl;
			// processPass();
		// default:
			//throw
	}
}
*/

