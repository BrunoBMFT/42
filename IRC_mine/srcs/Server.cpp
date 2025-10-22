#include "../includes/Server.hpp"

//*HELPERS
// noexcept(true)
int		mySocket(int __domain, int __type, int __protocol) {
	int temp = socket(__domain, __type, __protocol);
	if (temp == -1)
		throw (std::runtime_error("Cant create socket"));
	return (temp);
}

// noexcept(true)
void	myBind(int __fd, const sockaddr *__addr, socklen_t __len) {
	if (bind(__fd, __addr, __len) == -1)
		throw (std::runtime_error("Cant bind to IP/port"));
}

// noexcept(true)
void	myListen(int __fd, int __n) {
	if (listen(__fd, __n) == -1)
		throw (std::runtime_error("Cant listen"));
}


void	myPoll(pollfd *__fds, nfds_t __nfds, int __timeout) {
	if (poll(__fds, __nfds, __timeout) == -1)
		throw (std::runtime_error("Poll failed"));
}




//*CONSTRUCTORS
Server::Server(char *port, char *pass){
	_port = atoi(port);
	_pass = pass;

	_socket = mySocket(AF_INET, SOCK_STREAM, 0);

	int opt = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_port);
	inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);

	myBind(_socket, (sockaddr*)&server_addr, sizeof(server_addr));

	myListen(_socket, SOMAXCONN);

	std::cout << "Server open in port: " << _port << std::endl;
	//*colour version
	// std::cout << GREEN("Server open in port: ") << _port << std::endl;

	_srvPfd.fd = _socket;
	_srvPfd.events = POLLIN;
	_srvPfd.revents = 0;
}




//*GETTERS
int			Server::getSocket() { return (_socket); }
int			Server::getPort() { return (_port); }
std::string Server::getPass() { return (_pass); }






//todo server
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

//todo i think server should take care of accepting the client
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
	//todo put color on this
	std::cout << host << " manually connected on " << ntohs(client.sin_port) << std::endl;
	return (socket);
}

//todo i think server should take care of disconnecting the client
void	disconnectClient(std::vector<Client> &clients, std::vector<pollfd> &pfds, int i)
{
	std::cout << "The client disconnected" << std::endl;
	close (pfds[i].fd);
	clients.erase(clients.begin() + (i - 1));
}

//! SHOULD DEFINITELY BE IN CLIENT NOT IN SERVER
void	debugClientMessage(int id, char buf[])
{
	std::cout << "Client " << id + 1 << " said: " << buf;
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


void	Server::IRC()
{

	//todo server var?
	std::vector<pollfd> pfds;
	std::vector<Client> clients;
	
	
	//! should the server when being constructed already start the while loop?

	while (1)
	{
		//save the data
		restartLoop(&pfds, _srvPfd, clients);//_srvpfd, pfds, and clients might be able to not be parameters




		pfds.clear();
		pfds.push_back(_srvPfd);
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
			pfds.push_back(it->getPfd());

		myPoll(pfds.data(), pfds.size(), -1);
		if (pfds[0].revents & POLLIN)//* Client Connecting
		{
			int socket = acceptClient(_socket);//server should be the one calling this
			clients.push_back(Client(socket));
		}
		for (int i = 1; i < pfds.size(); i++)//*loop through clients
		{
			/*
				Ok so I could handle all this inside client, but then id have to call server again to disconnect client
				so maybe ill actually handle this inside only server, and call the client to save buf and to debug the message
			*/
			if (pfds[i].revents & POLLIN)
			{
				//!client var
				char buf[512];
				
				int bytesRecv = recv(pfds[i].fd, buf, sizeof(buf), 0);//myrecv
				if (bytesRecv == -1)
					throw (std::runtime_error("There was a connection issue"));
				if (bytesRecv == 0)
					disconnectClient(clients, pfds, i);
				else {
					buf[bytesRecv] = 0;
					debugClientMessage(clients[i - 1].getId(), buf);//the i - 1 is stupid


					if (shouldServerExit(*this, clients, buf))//TEMPORARY, put in processCommand?
						return ;

					// processCommand(clients[i - 1], buf);
/* 
	cases client should disconnect:
		client tries to talk before setting nick or user
		client send data with no newline or too long
		sends QUIT command
		ping timeout
*/
				}
			}
		}
	}
	close(_socket);
}