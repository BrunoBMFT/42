#include "../includes/Server.hpp"
#include "../includes/Client.hpp"


void	Server::registration(int i)
{
	if (!_clients[i].isAuthenticated()) {
		tryAuthClient(i);
		return ;
	}
	if (strncmp(_clients[i].getBuf(), "USER ", 5) == 0)
		registerUser(i);
	else if (strncmp(_clients[i].getBuf(), "NICK ", 5) == 0)
		registerNick(i);
	else {
		sendToClient(i, _clients[i].getNick(), ERR_NOTREGISTERED);
		serverLog(_clients[i].getNick(), "not registered, cant talk");
	}
}



//*Authenticating
void	Server::tryPass(int i, char *bufPass)
{
	std::string line(bufPass);
	size_t pos = 0;
	for (int i = 0; i < 1; ++i)
		pos = line.find(' ', pos + 1);
	if (strcmp(line.substr(pos + 1).c_str(), _pass.c_str()) != 0) {
		//todo can hard code to sender be "*"
		sendToClient(i, _clients[i].getNick(), ERR_PASSWDMISMATCH);
		return (serverLog(_clients[i].getNick(), "guessed the password wrong"));
	}

	_clients[i].setAuthenticated(true);
	//todo can hard code to sender be "*"
	sendToClient(i, _clients[i].getNick(), PASSACCEPT);
	serverLog(_clients[i].getNick(), "has authenticated, needs to register");
}
void	Server::tryAuthClient(int i)
{
	char *bufPass = _clients[i].getBuf();
	bufPass[_clients[i]._bytesRecv - 1] = '\0'; 
	if (strncmp(_clients[i].getBuf(), "PASS ", 5) != 0) {
	//todo can hard code to sender be "*"
		sendToClient(i, _clients[i].getNick(), ERR_NOTAUTH);
		return (serverLog(_clients[i].getNick(), "is not authenticated, cannot talk"));
	}
	tryPass(i, bufPass);
}



//*GETTERS FROM LINE
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

//*Registration
void	Server::welcomeClient(int i)
{
	std::string welcome = "Welcome to the " + _name + " Network, "
		+ _clients[i].getNick() + "[!" + _clients[i].getUsername() 
		+ "@"+ "host" + "]";//hardcoded
	sendToClient(i, _clients[i].getNick(), welcome);
	std::string todo = "The rest of the welcome message will come after";

	sendToClient(i, _clients[i].getNick(), todo);
	//RPL_YOURHOST 
	//RPL_CREATED 
	//RPL_MYINFO
	//RPL_ISUPPORT (prob not needed)
	//LUSERS?
	//MOTD
}
void	Server::checkRegistration(int i)
{
	if (!_clients[i].getNick().empty() && !_clients[i].getUsername().empty() && !_clients[i].getRealname().empty() && _clients[i].getNick() != "*")
	{
		_clients[i].setRegistered(true);
		welcomeClient(i);
	}
}

void	Server::registerUser(int i)//should be client class, not server class
{
	std::cout << _clients[i].getNick() << " set their username to: ";//check if here is getNick
	_clients[i].setUsername(getUsername(_clients[i].getBuf()));
	_clients[i].setRealname(getRealname(_clients[i].getBuf()));
	std::cout << _clients[i].getUsername() << " || " << _clients[i].getRealname() << std::endl;
	checkRegistration(i);
}
void	Server::registerNick(int i)//should be client class, not server class
{
	std::cout << _clients[i].getNick() << " set their nick to: ";
	_clients[i].setNick(getNick(_clients[i].getBuf()));
	std::cout << _clients[i].getNick() << std::endl;
	checkRegistration(i);
}
