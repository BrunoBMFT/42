#include "../includes/Server.hpp"

//todo do the isRegistered() part and the welcome part, then remove all comments and make it readable, then channels!!!

//todo Channel logic
/* 
when a message is sent to server, save the channel that the client who sent it used, 
then go to that channels ClientsInChannel, then loop through getId to find which clients to sendInfo to




	class channel
	{
		vector ClientsInChannel (saves their id)
		
	}
	
	
	Server
	{
		vector Channel
	}


	


	WHERE WOULD THIS GO THO????
	SHALL I JUST TEST IT AFTER PROCESSING REGISTRATION???
	while (_clients[i]) 
	{
		if (_clients[i].getId() == ClientsInChannel)      FIND INSIDE THE VECTOR OF ClientsInChannel
		{
			sendToClient(_clients[i], LINE_TO_SEND);
		}
	}


	commandJoin(std::string str) {
		if (Channel with name str doesnt exist)
		{
			createChannel()
			save _clients[i].getId() into channel.ClientsInChannel
		}
		else
		{
			save _clients[i].getId() into channel.ClientsInChannel
		}
	}



 */






//*CONSTRUCTORS
Server::Server(char *port, char *pass) {
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


//todo here STARTS REGISTRATION
std::string getUsername(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 1; ++i)
        pos = line.find(' ', pos + 1);
	std::string username = line.substr(pos + 1, line.find(' ', pos + 2) - pos - 1);
	while (!username.empty() && (username[username.size() - 1] == '\r' || username[username.size() - 1] == '\n'))
		username.erase(username.size() - 1);
    return (username);
}
std::string getRealname(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 4; ++i)
        pos = line.find(' ', pos + 1);
	std::string realname = line.substr(pos + 1);
	while (!realname.empty() && (realname[realname.size() - 1] == '\r' || realname[realname.size() - 1] == '\n'))
		realname.erase(realname.size() - 1);
    return (realname);
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

	while (!nickname.empty() && (nickname[nickname.size() - 1] == '\r' || nickname[nickname.size() - 1] == '\n'))
		nickname.erase(nickname.size() - 1);
	return (nickname);
}


void	sendToClient(Client client, std::string str) {
	std::string reply = client.getNick() + " :"+ str + "\r\n";
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
}


void	Server::tryPass(int i, char *bufPass)
{
	std::string line(bufPass);
	size_t pos = 0;
	for (int i = 0; i < 1; ++i)
		pos = line.find(' ', pos + 1);
	if (strcmp(line.substr(pos + 1).c_str(), _pass.c_str()) != 0) {
		sendToClient(_clients[i], ERR_PASSWDMISMATCH);
		throw std::runtime_error(" guessed the password wrong");
	}

	_clients[i].setAuthenticated(true);
	sendToClient(_clients[i], PASSACCEPT);//irc servers usually wait silently here
	std::cout << "* has authenticated, needs to register" << std::endl;
	throw std::runtime_error(" has authenticated, needs to register");//not runtime_error
}


void	Server::tryAuthClient(int i, int bytesRecv)
{
	//have a commandPass() for when already registered, to send error message
	char *bufPass = _clients[i].getBuf();
	bufPass[bytesRecv - 1] = '\0'; 
	if (strncmp(_clients[i].getBuf(), "PASS ", 5) != 0) {
		sendToClient(_clients[i], NOTAUTH);
		throw std::runtime_error(" is Not Authenticated, cannot talk");
	}
	tryPass(i, bufPass);
}




void	Server::checkRegistration(int i) {
	if (!_clients[i].getNick().empty() && !_clients[i].getUsername().empty() && !_clients[i].getRealname().empty())
	{
		_clients[i].setRegistered(true);
		sendToClient(_clients[i], "Welcome");
		//RPL_WELCOME 
		//RPL_YOURHOST 
		//RPL_CREATED 
		//RPL_MYINFO
		//RPL_ISUPPORT (prob not needed)
		//LUSERS?
		//MOTD
	}
}



void	Server::registerUser(int i)
{
	_clients[i].setUsername(getUsername(_clients[i].getBuf()));
	_clients[i].setRealname(getRealname(_clients[i].getBuf()));
	std::cout << "Username set to: " << _clients[i].getUsername() << " || " << _clients[i].getRealname() << std::endl;
	checkRegistration(i);
}
void	Server::registerNick(int i)
{
	_clients[i].setNick(getNick(_clients[i].getBuf()));
	std::cout << "Nick set to: " << _clients[i].getNick() << std::endl;
	checkRegistration(i);
}

//todo here ENDS REGISTRATION


void	Server::processCommand(int i, int bytesRecv)
{
	// std::cout << YELLOW("Debug: ") << "Client " << _clients[i].getNick()<< " said: " << _clients[i].getBuf();
	if (!_clients[i].isAuthenticated()) {
		tryAuthClient(i, bytesRecv);
		return ;
	}
	if (!_clients[i].isRegistered()) {
		
		if (strncmp(_clients[i].getBuf(), "USER ", 5) == 0)
			registerUser(i);
		else if (strncmp(_clients[i].getBuf(), "NICK ", 5) == 0)
			registerNick(i);
		else {
			sendToClient(_clients[i], NOTREGISTERED);
			throw std::runtime_error(" not registered, cant talk");
		}
	}
	else {
		sendToClient(_clients[i], _clients[i].getBuf());
	}
}



int	Server::handleClientPoll(int i)
{
	char buf[512];
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



