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

	// std::cout << "Server open in port: " << _port << std::endl;
	std::cout << GREEN("Server open in port: ") << _port << std::endl;

	_srvPfd.fd = _socket;
	_srvPfd.events = POLLIN;
	_srvPfd.revents = 0;

	_clients.push_back(Client());//This is so that we dont have to work with _clients[i - 1]
}

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
	std::vector<Client>::iterator it = _clients.begin();//stupid fucking fix
	it++;
	while (it != _clients.end()){
		_pfds.push_back(it->getPfd());
		it++;
	}
}

//*Disconnect client when client exits
//todo tell client its disconnecting using sendToClient()
void	Server::disconnectClient(Client client, int i)
{
	//remove Client as parameter
	std::cout << "Client " << client.getUsername() << " disconnected" << std::endl;

	close (_pfds[i].fd);
	_clients.erase(_clients.begin() + i - 1);
}

//this is just testing
bool	Server::shouldServerExit(char buf[])
{
	if (strncmp(buf, "exit", 4) == 0) {
		std::cout << "exiting server" << std::endl;
		for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
			close(it->getSocket());
		close(_socket);
		return (true);
	}
	return (false);
}

enum	pollCondition//fucking stupid find a better solution
{
	DISCONNECT,
	EXIT,
	OK
};


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


void	sendToClient(Client client, std::string str) {
	//have str be defines in .hpp
	//also have the " :" be hardcoded here?
	std::string reply = client.getNick() + str + "\r\n";//check if std::endl does the same as \r\n
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
}


void	Server::tryPass(int i, char *bufPass)
{
	std::string line(bufPass);
	size_t pos = 0;
	for (int i = 0; i < 1; ++i)
		pos = line.find(' ', pos + 1);
	if (strcmp(line.substr(pos + 1).c_str(), _pass.c_str()) != 0) {
		sendToClient(_clients[i], " :Password incorrect");
		throw std::runtime_error(" guessed the password wrong");
	}

	_clients[i].setAuthenticated(true);
	sendToClient(_clients[i], " :Authenticated, set User and Nick to register");
	throw std::runtime_error(" has authenticated, needs to register");//not runtime_error
}


void	Server::tryAuthClient(int i, int bytesRecv)//todo STUPID TO SEND bytesRecv LIKE THIS
{
	//have a commandPass() for when already registered, to send error message
	char *bufPass = _clients[i].getBuf();
	bufPass[bytesRecv - 1] = '\0'; //todo stupid to pass bytesRecv just for this
	if (strncmp(_clients[i].getBuf(), "PASS ", 5) != 0) {
		sendToClient(_clients[i], " :Not authenticated");
		throw std::runtime_error(" is Not Authenticated, cannot talk");
	}
	tryPass(i, bufPass);
}

void	Server::registerUser(int i)
{
	_clients[i].setUsername(getUsername(_clients[i].getBuf()));
	_clients[i].setRealname(getRealname(_clients[i].getBuf()));
	std::cout << "Username set to: " << _clients[i].getUsername() << " || " << _clients[i].getRealname() << std::endl;
}
void	Server::registerNick(int i)
{
	_clients[i].setNick(getNick(_clients[i].getBuf()));
	std::cout << "Nick set to: " << _clients[i].getNick() << std::endl;
}


//todo CHECK ALL LOGS OF SERVER AND CLIENT
//rename to processRegistration?
//it then put isRegistered to true, and prints the welcome messages
void	Server::processCommand(int i, int bytesRecv)
{
	if (!_clients[i].isAuthenticated()) {
		tryAuthClient(i, bytesRecv);//STUPID, dont send bytesRecv like this
		return ;
	}
	std::cout << "Client " << _clients[i].getNick()<< " said: " << _clients[i].getBuf();
	if (strncmp(_clients[i].getBuf(), "USER ", 5) == 0)
		registerUser(i);//rename
	if (strncmp(_clients[i].getBuf(), "NICK ", 5) == 0)
		registerNick(i);//rename
	//if (hasUser and hasNick) then isRegistered = true
	//welcomeUser
	//todo RPL_WELCOME RPL_YOURHOST RPL_CREATED RPL_MYINFO	 after registering
}



int	Server::handleClientPoll(int i)//i here is only sent so that _pfds and _clients are at the same index
{
	char buf[512];//this can change for a vector if needed
	int bytesRecv = myRecv(_pfds[i].fd, buf, sizeof(buf), 0);
	if (bytesRecv == 0) {
		disconnectClient(_clients[i], i);
		return (DISCONNECT);
	}
	buf[bytesRecv] = 0;

	if (shouldServerExit(buf))
		return (EXIT);

	_clients[i].setBuf(buf);


	try {
		processCommand(i, bytesRecv);
	} catch(const std::exception& e) {
		//this should be server logs
		std::cerr << YELLOW("Client log: ") << _clients[i].getNick() << e.what() << std::endl;
	}
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
