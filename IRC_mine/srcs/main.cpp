#include "../includes/IRC.hpp"
//when saying study, learn the returns, what the functions can do, whatever else needed

class Server
{
	private:
		int _socket;
		sockaddr_in server_addr;//study sockaddr_in and sockaddr
		// int _port;
	public:
		Server() {
		//! ALL OF THIS SHOULD GO IN SERVER CREATION RIGHT? 
		//! SINCE ALL IT DOES IS CREATE A SERVER WITH A PORT AND A PASSWORD, 
		//! EVERYTHING SHOULD RUN SMOOTHLY, right?
			_socket = socket(AF_INET, SOCK_STREAM, 0);//*study socket, sockstream, AF_INET is IPv4
			if (_socket == -1)
				throw (std::runtime_error("Cant create socket"));

			//study this part
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(6667);//study htons(), changed from 54000 to 6667
			inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);//study inet_pton(), i guess save port in class

			if (bind(_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
				throw (std::runtime_error("Cant bind to IP/port"));

			if (listen(_socket, SOMAXCONN) == -1)//study listen()
				throw (std::runtime_error("Cant listen"));

		}

		int getSocket() {
			return _socket;
		}
};

void	IRC()
{
	//create a socket
	//bind the socket to IP / port
	//mark the socket for listening in

	//accept the client call
	//close the listening socket

	//wait for message from client
	//receive message, print it, and echo it

	//close client socket
	

	Server srv;//it will take parameters after

	//todo CLIENT
	sockaddr_in	client;
	socklen_t	clientSize = sizeof(client);
	char		host[NI_MAXHOST];
	char		svc[NI_MAXSERV];

	//save client socket (fd ig) in client class
	int clientSocket = accept(srv.getSocket(), (sockaddr*)&client, &clientSize);//study accept()
	if (clientSocket == -1)
		throw (std::runtime_error("Problem with client connecting"));

	//! THIS SOCKET WILL NEVER CLOSE
	// close(srv.getSocket());//!why close the listening?
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
	//todo CLIENT



	//todo EXCHANGE
	char	buf[4096];
	while (1)
	{
		//clear buffer
		memset(buf, 0, 4096);
		//waits for a message
		int bytesRecv = recv(clientSocket, buf, 4096, 0);//study recv()
		if (bytesRecv == -1)
			throw (std::runtime_error("There was a connection issue"));
		if (bytesRecv == 0) {
			std::cout << "The client disconnected" << std::endl;
			break ;
		}
		std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

		send(clientSocket, buf, bytesRecv + 1, 0);//study send()
	}

	close(clientSocket);
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
