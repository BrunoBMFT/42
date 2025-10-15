#include "../includes/IRC.hpp"
#include <vector>
#include <poll.h>
/*
	create a socket
	bind the socket to IP / port
	mark the socket for listening in

	accept the client call
	close the listening socket

	wait for message from client
	receive message, print it, and echo it

	close client socket
*/
//when saying study, learn the returns, what the functions can do, whatever else needed

class Server
{
	private:
		int _srvSocket;//rename to _socket
		sockaddr_in server_addr;//study sockaddr_in and sockaddr
		// int _port;
	public:
		Server() {
		//! ALL OF THIS SHOULD GO IN SERVER CREATION RIGHT? 
		//! SINCE ALL IT DOES IS CREATE A SERVER WITH A PORT AND A PASSWORD, 
		//! EVERYTHING SHOULD RUN SMOOTHLY, right?
			_srvSocket = socket(AF_INET, SOCK_STREAM, 0);//*study socket, sockstream, AF_INET is IPv4
			if (_srvSocket == -1)
				throw (std::runtime_error("Cant create socket"));

			int opt = 1;
			setsockopt(_srvSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//study
			//study this part
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(6667);//study htons(), changed from 54000 to 6667
			inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);//study inet_pton(), i guess save port in class

			//if program closes badly, socket might still be in use by bind
			//fix is use SO_REUSEADDR, using the setsockopt() func
			if (bind(_srvSocket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
				throw (std::runtime_error("Cant bind to IP/port"));

			if (listen(_srvSocket, SOMAXCONN) == -1)//study listen()
				throw (std::runtime_error("Cant listen"));
		}

		int getSrvSocket() {//rename to getSocket
			return _srvSocket;
		}
};



class Client
{
	private:
	public:
		//private vars
		int _clientSocket;//rename to _socket
		pollfd pfd;
		Client(int srvSocket) {
			//*pollfds attempt
			// _clientSocket = srvSocket;
			// pfd.fd = srvSocket;
			// pfd.events = POLLIN;
			// pfd.revents = 0;

			sockaddr_in	client;
			socklen_t	clientSize = sizeof(client);
			char		host[NI_MAXHOST];
			char		svc[NI_MAXSERV];

			//save client socket (fd ig) in client class
			_clientSocket = accept(srvSocket, (sockaddr*)&client, &clientSize);//study accept()
			if (_clientSocket == -1)
				throw (std::runtime_error("Problem with client connecting"));

			memset(host, 0, NI_MAXHOST);//cleans whatever garbage data was in host before (doesnt feel needed but sure)
			memset(svc, 0, NI_MAXSERV);

			//save client_addr in client class
			int result = getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);//study what this is for
			if (result)
				std::cout << host << " connected on " << svc << std::endl;
			else{//this seems stupid
				inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
				std::cout << host << " manually connected on " << ntohs(client.sin_port) << std::endl;//study ntohs()
				//study why do things manually like this
			}
		}

		int	getClientSocket() {//rename to getSocket
			return _clientSocket;
		}
};

void	IRC()
{

	Server srv;//it will take parameters after, for now its hard coded

	
	//in client class, have the socket, the pfd same as socket, and pfd.events and revents
	//create a pollfd for server and set it up
	//create vector for clients
	//start loop
	//	create vector of pollfd
	//	put client pfd into pollfd vector
	//	poll()
	//	check server POLLIN for new client, accept client, and place that fd into the client vector
	//	check clients and print whatever client prints
	//	update server.pfd.revents to be same as pfds[0].revents
	//	update revents of each client



	//* poll() test
	/*
		std::vector<Client> cls;
		Client cl1(srv.getSrvSocket()), cl2(srv.getSrvSocket());
		cls.push_back(cl1);
		cls.push_back(cl2);

		//study pollfd struct, and POLLIN

		struct pollfd pfds[3];
		pfds[0].fd = cl1.getClientSocket();
		pfds[0].events = POLLIN;
		pfds[0].revents = 0;
		pfds[1].fd = cl2.getClientSocket();
		pfds[1].events = POLLIN;
		pfds[1].revents = 0;

		while (1)
		{
			if (poll(pfds, 2, -1) == -1)
				throw (std::runtime_error("Poll failed"));
			for (int i = 0; i < 2; i++) {
				if (pfds[i].revents & POLLIN) {
					char buf[512];
					int n = recv(pfds[i].fd, buf, sizeof(buf), 0);
					buf[n] = 0;
					std::cout << "Client " << i + 1 << " said: " << buf;
				}
			}
		}
	*/

	//* non poll() test
	/*
		Client cl1(srv.getSrvSocket()), cl2(srv.getSrvSocket());
	
	
		//todo EXCHANGE
		char	buf[4096];
		while (1)
		{
			//clear buffer
			memset(buf, 0, 4096);
			//waits for a message
			int bytesRecv = recv(cl1.getClientSocket(), buf, 4096, 0);//study recv()
			if (bytesRecv == -1)
				throw (std::runtime_error("There was a connection issue: 1"));
			if (bytesRecv == 0) {
				std::cout << "The client disconnected" << std::endl;
				break ;
			}
			std::cout << "Received from 1: " << std::string(buf, 0, bytesRecv) << std::endl;
	
			send(cl1.getClientSocket(), buf, bytesRecv + 1, 0);//study send()
		}
	*/

	close(srv.getSrvSocket());
	//close clients
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
