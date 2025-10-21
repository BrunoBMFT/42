#include "../includes/IRC.hpp"

//use MyFunc for functions that need checking
//put colors in debugs
//put stuff in classes to be able to not have that many parameters for each function
// the actual next thing i should do is manage to print stuff on client 1 that client 2 sent

class Server
{
	private:
		int				_port;
		std::string		_pass;
		int				_socket;
		sockaddr_in		server_addr;
	public:
		Server(char *port, char *pass)
		{
			_port = atoi(port);
			_pass = pass;
			//have a function that calls trySocket() with same params, so that the throw is hidden
			_socket = socket(AF_INET, SOCK_STREAM, 0);
			if (_socket == -1)
				throw (std::runtime_error("Cant create socket"));

			int opt = 1;
			setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(_port);
			inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);

			//have a function that calls tryBind() with same params, so that the throw is hidden
			if (bind(_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
				throw (std::runtime_error("Cant bind to IP/port"));

			//have a function that calls tryListen() with same params, so that the throw is hidden
			if (listen(_socket, SOMAXCONN) == -1)
				throw (std::runtime_error("Cant listen"));
			
			std::cout << "Server open in port: " << _port << std::endl;
		}

		int		getSocket() {
			return (_socket);
		}
		int		getPort() {
			return (_port);
		}
		std::string getPass() {
			return (_pass);
		}
};

//todo when setting username and nick, have the setUser and setNick do the parsing
class Client
{
	private:
		static int	_globalId;
		int			_id;
		int			_socket;
		pollfd		_pfd;
	public:
		Client(int srvSocket)
		{
			_id = _globalId++;
			_socket = srvSocket;
			_pfd.fd = _socket;
			_pfd.events = POLLIN;
			_pfd.revents = 0;
		}

		int		getId() {
			return (_id);
		}
		int		getSocket() {
			return (_socket);
		}
		pollfd	&getPfd() {
			return (_pfd);
		}
};

//so weird so random
int Client::_globalId;

bool	shouldServerExit(Server srv, std::vector<Client> clients, char buf[])
{
	if (strncmp(buf, "exit", 4) == 0) {
		std::cout << "exiting server\n";
		for (std::vector<Client>::iterator client_it = clients.begin(); client_it != clients.end(); client_it++)
			close(client_it->getSocket());
		close(srv.getSocket());
		return (true);
	}
	return (false);
}

int		acceptClient(int srvSocket)
{
	int			socket;
	sockaddr_in	client;
	socklen_t	clientSize = sizeof(client);
	char		host[NI_MAXHOST];
	
	socket = accept(srvSocket, (sockaddr*)&client, &clientSize);
	if (socket == -1)
		throw (std::runtime_error("Problem with client connecting"));
	memset(host, 0, NI_MAXHOST);
	
	inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	std::cout << host << " manually connected on " << ntohs(client.sin_port) << std::endl;
	return (socket);
}

void	disconnectClient(std::vector<Client> &clients, std::vector<pollfd> &pfds, int i)
{

	std::cout << "The client disconnected" << std::endl;
	close (pfds[i].fd);
	clients.erase(clients.begin() + (i - 1));
}

void	debugClientMessage(int id, char buf[])
{
	std::cout << "Client " << id + 1 << " said: " << buf;
}


/* 
	if (!strcmp(buf, pass))
		std::cout << "Password correct\nClient should now be able to set user and talk\n";
	else {
		std::cout << "Password incorrect\n";//!send the err instead of this
	// ! send ERR_PASSWDMISMATCH (464)
		send(clients[i - 1].getSocket(), "Client closing", 15, 0);//!send the err instead of this
		close (pfds[i].fd);
		clients.erase(clients.begin() + (i - 1));
	}
*/

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

//use getPass()
void	IRC(char *port, char *pass)
{
	Server srv(port, pass);

	pollfd srv_pfd;
	srv_pfd.fd = srv.getSocket();
	srv_pfd.events = POLLIN;
	srv_pfd.revents = 0;
	std::vector<pollfd> pfds;
	
	std::vector<Client> clients;
	
	while (1)
	{
		//save the data
		pfds.clear();
		pfds.push_back(srv_pfd);
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
			pfds.push_back(it->getPfd());

		if (poll(pfds.data(), pfds.size(), -1) == -1)
			throw (std::runtime_error("Poll failed"));
		if (pfds[0].revents & POLLIN)//* Client Connecting
		{
			int socket = acceptClient(srv.getSocket());
			clients.push_back(Client(socket));
		}
		for (int i = 1; i < pfds.size(); i++)//*loop through clients
		{
			if (pfds[i].revents & POLLIN)
			{	
				char buf[512];
				int bytesRecv = recv(pfds[i].fd, buf, sizeof(buf), 0);//myrecv
				if (bytesRecv == -1)
					throw (std::runtime_error("There was a connection issue: 1"));
				if (bytesRecv == 0)
					disconnectClient(clients, pfds, i);
				else {
					buf[bytesRecv] = 0;
					debugClientMessage(clients[i - 1].getId(), buf);


					if (shouldServerExit(srv, clients, buf))//TEMPORARY, put in processCommand?
						return ;

					processCommand(clients[i - 1], buf);
/* 
	cases client should disconnect 
	client tries to talk before setting nick or user
	client send data with no newline or too long
	sends QUIT command
	ping timeout
*/
				}
			}
		}
	}
	close(srv.getSocket());
}

int		main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "Bad arguments" << std::endl;
		return 1;
	}
	try {
		IRC(av[1], av[2]);
	} catch (std::exception &e) {
		std::cerr << "Exception caught! " << e.what() << std::endl;
	}

	return 0;
}



/* 
	Client needs to register itself in server before using stuff like JOIN or PRIVMSG
	client should send info:
		recommended order by ircdocs:
			CAP LS 302 (will i be able to ignore this??)
			PASS
			NICK and USER
			capability negotiation (what??)
			SASL (more what??)
			CAP END

	have server send a ping, and client send a pong

	server MUST send:
		RPL_WELCOME
		RPL_YOURHOST
		RPL_CREATED
		RPL_MYINFO
		at least RPL_ISUPPORT numeric to the client
		may send other numerics and messages
		Server should respond as if client sent LUSERS and return numerics
		Server should respond as if client sent MOTD
		if user has client modes, set them automatically

	(all this info idk what it means xD)

	(this statement is now kinda fake)
	Client needs to put correct pass to be able to talk, 
	otherwise it gets disconnected and socket closed
	(this statement is now kinda fake)
*/
