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

	_clients.push_back(Client());//This is so that we dont have to work with _clients[i - 1]
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
	//changes it++ to ++it because it should skip the first one, hopefully it works
	std::vector<Client>::iterator it = _clients.begin();
	it++;
	while (it != _clients.end()){
		_pfds.push_back(it->getPfd());
		it++;
	}
}

//*Disconnect client when client exits
void	Server::disconnectClient(Client client, int i)
{
	std::cout << "Client " << client.getId() << " disconnected" << std::endl;

	close (_pfds[i].fd);
	_clients.erase(_clients.begin() + i - 1);//! CHECK IF THIS IS CORRECT
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


//!COLETESCOLETESCOLETESCOLETESCOLETESCOLETES
std::string getUsername(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 1; ++i)
        pos = line.find(' ', pos + 1);
    return line.substr(pos + 1, line.find(' ', pos + 2) - pos - 1);
}

std::string getRealname(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 4; ++i)
        pos = line.find(' ', pos + 1);
    return line.substr(pos + 1);
}

std::string getNick(const std::string &line) {
    size_t pos = 0;
	std::string nickname;
    for (int i = 0; i < 1; ++i)
        pos = line.find(' ', pos + 1);
	nickname = line.substr(pos + 1, line.find(' ', pos + 2) - pos - 1);
	if (nickname[0] == ':' || nickname == "#" || !strncmp(nickname.c_str(), "#&", 2) || !strncmp(nickname.c_str(), "&#", 2) || nickname.empty())
		return ("");
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (nickname[i] == ' ')
			return ("");
	}
    return (nickname);
}
//!COLETESCOLETESCOLETESCOLETESCOLETESCOLETES


//like sending a client as parameter is bad if i have classes right?
int	Server::handleClientPoll(int i)//send specific client as well?
{
	char buf[512];//this can change for a vector if needed
	int bytesRecv = myRecv(_pfds[i].fd, buf, sizeof(buf), 0);
	if (bytesRecv == 0) {
		disconnectClient(_clients[i], i);//NO NEED TO SEND CLIENTS LIKE THIS
		return (DISCONNECT);
	}
	buf[bytesRecv] = 0;
	// debugClientMessage(_clients[i], buf);

	if (shouldServerExit(buf))
		return (EXIT);


	//!COLETESCOLETESCOLETESCOLETESCOLETESCOLETES
	//todo put this in processCommand function, and processCommand will be coletes?
	if (!_clients[i].isAuthenticated())
	{
		char *bufPass = buf/* strncpy(buf, bufPass, bytesRecv) */;
		bufPass[bytesRecv - 1] = '\0'; //removing \r\n
		std::cout << "Mine: " << bufPass << "\tOrig: " << _pass << "\tValue: " << (bufPass == _pass) << std::endl;
		if (!strncmp(buf, "PASS ", 5)/* strcmp(bufPass, &pass[0]) == 0 */)
		{
			std::string line(bufPass);
			size_t pos = 0;
			for (int i = 0; i < 1; ++i)
				pos = line.find(' ', pos + 1);
			std::cout << "Extracted pass: " << line.substr(pos + 1) << std::endl;	
			if (strcmp(line.substr(pos + 1).c_str(), _pass.c_str()) == 0)
			{
				std::cout << "Password correct\nClient should now be able to set user and talk\n";
				_clients[i].setAuthenticated(true);
			}
			else {
				std::cout << "Password incorrect\n";//Client shouldnt close, send errPass back, check comments
				//function for cout, throwing the error. 
				//handleClientPoll should have a try catch, and processcommand which is where this will be will throw here
			}
		}
		else {
			std::cout << "Client cannot talk\n";
			//send error message to try catch here
		}
	}
	else
	{
		std::cout << "Client " << _clients[i].getUsername()<< " said: " << buf;
		if (strncmp(buf, "USER ", 5) == 0)
		{
			_clients[i].setUsername(getUsername(buf));
			_clients[i].setRealname(getRealname(buf));
			std::cout << "Username set to: " << _clients[i].getUsername() << " || " << _clients[i].getRealname() << std::endl;
		}
		if (strncmp(buf, "NICK ", 5) == 0)
		{
			_clients[i].setNick(getNick(buf));
			std::cout << "Nick set to: " << _clients[i].getNick() << std::endl;
		}
	}
	//!COLETESCOLETESCOLETESCOLETESCOLETESCOLETES

	// TODO processCommand(clients[i - 1], buf);
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
	Have a function called printInfo, that will have client id, nick and/or user, authenticated, and the command
	maybe for this, buffer or command will have to be saved onto client

	also, hard code a client with info already in it and pass a command as if it was written to test the parsing
*/

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

