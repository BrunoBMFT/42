#include "../includes/IRC.hpp"

class Server
{
	private:
		int				_socket;//rename to _socket
		sockaddr_in		server_addr;//study sockaddr_in and sockaddr
		int _port;
	public:
		Server()
		{
			_port = 6667;//hard coded, will be input
			_socket = socket(AF_INET, SOCK_STREAM, 0);//*study socket, sockstream, AF_INET is IPv4
			if (_socket == -1)
				throw (std::runtime_error("Cant create socket"));

			int opt = 1;
			setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//study
			//study this part
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(_port);//study htons(), 
			inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);//study inet_pton(), i guess save port in class

			//if program closes badly, socket might still be in use by bind
			//fix is use SO_REUSEADDR, using the setsockopt() func
			if (bind(_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
				throw (std::runtime_error("Cant bind to IP/port"));

			if (listen(_socket, SOMAXCONN) == -1)//study listen()
				throw (std::runtime_error("Cant listen"));
			
			std::cout << "Server open in port: " << _port << std::endl;
		}

		int getSocket() {
			return (_socket);
		}
};


class Client
{
	private:
		//have a int id for each client
		int			_socket;
		pollfd		_pfd;
	public:

		Client(int srvSocket)
		{
			sockaddr_in	client;
			socklen_t	clientSize = sizeof(client);
			char		host[NI_MAXHOST];
			char		svc[NI_MAXSERV];
			
			//accept should be outside?
			_socket = accept(srvSocket, (sockaddr*)&client, &clientSize);//study accept()
			if (_socket == -1)
				throw (std::runtime_error("Problem with client connecting"));
			memset(host, 0, NI_MAXHOST);
			//!save client_addr in client class
			//kinda want to connect them manually all the time
			int result = getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);
			if (result)
				std::cout << host << " connected on " << svc << std::endl;
			else{//this seems stupid
				inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
				std::cout << host << " manually connected on " << ntohs(client.sin_port) << std::endl;//study ntohs()
			}
			_pfd.fd = _socket;
			_pfd.events = POLLIN;
			_pfd.revents = 0;
		}

		int	getSocket() {
			return (_socket);
		}
		pollfd getPfd() {
			return (_pfd);
		}
};

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

void	disconnectClient(std::vector<pollfd> pfds, std::vector<Client> clients, int i)
{
	std::cout << "The client disconnected" << std::endl;
	close (pfds[i].fd);
	clients.erase(clients.begin() + (i - 1));
}

void	IRC()
{

	Server srv;//it will take parameters after, for now its hard coded


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
		if (pfds[0].revents & POLLIN) {
			std::cout << "client connecting" << std::endl;
			clients.push_back(Client(srv.getSocket()));
		}
		for (int i = 1; i < pfds.size(); i++) {
			if (pfds[i].revents & POLLIN) {	
				char buf[512];
				int bytesRecv = recv(pfds[i].fd, buf, sizeof(buf), 0);
				if (bytesRecv == -1)
					throw (std::runtime_error("There was a connection issue: 1"));
				if (bytesRecv == 0) {
					std::cout << "The client disconnected" << std::endl;
					close (pfds[i].fd);
					clients.erase(clients.begin() + (i - 1));
				}
					// disconnectClient(pfds, clients, i);
				else
				{
					buf[bytesRecv] = 0;
					std::cout << "Client " << i << " said: " << buf;
					send(clients[i - 1].getSocket(), buf, bytesRecv + 1, 0);
					if (shouldServerExit(srv, clients, buf))//TEMPORARY
						return ;
				}
			}
		}
	}
	close(srv.getSocket());
}

int		main(int ac, char **av)
{
	// if (ac != 3) {
	// 	std::cout << "Bad arguments" << std::endl;
	// 	return 1;
	// }
	try {
		IRC();
	} catch (std::exception &e) {
		std::cerr << "Exception caught! " << e.what() << std::endl;
	}

	return 0;
}



