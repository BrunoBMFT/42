#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
//when saying study, learn the returns, what the functions can do, whatever else needed

//class for server

void	createServer()
{

	//create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);//*study socket, sockstream, AF_INET is IPv4
	if (listening == -1)
		throw (std::runtime_error("Cant create socket"));
	
	//bind the socket to IP / port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);//study htons()
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);//study inet_pton()

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
		throw (std::runtime_error("Cant bind to IP/port"));

	//mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1)//study listen()
		throw (std::runtime_error("Cant listen"));
	
	//accept the call
	sockaddr_in	client;
	socklen_t	clientSize = sizeof(client);
	char		host[NI_MAXHOST];
	char		svc[NI_MAXSERV];

	int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);//study accept()
	if (clientSocket == -1)
		throw (std::runtime_error("Problem with client connecting"));

	//close the listening socket
	close(listening);//why close the listening?
	memset(host, 0, NI_MAXHOST);//cleans whatever garbage data was in host before (doesnt feel needed but sure)
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, svc, NI_MAXSERV, 0);//study what this is for
	//if getnameinfo fails, this is a cheat
	if (result)
		std::cout << host << " connected on " << svc << std::endl;
	else{//the case where getnameinfo fails{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;//study ntohs()
		//study why do things manually like this
	}

	//while recieving message, echo the message

	char	buf[4096];
	while (1)
	{
		//clear buffer
		memset(buf, 0, 4096);
		//wait for a message
		int bytesRecv = recv(clientSocket, buf, 4096, 0);//study recv()
		if (bytesRecv == -1)
			throw (std::runtime_error("There was a connection issue"));
		if (bytesRecv == 0) {
			std::cout << "The client disconnected" << std::endl;
			break ;
		}
		//display message
		std::cout << "Received: " << buf/*string(buf, 0, bytesRecv)*/ << std::endl;

		//resend message
		send (clientSocket, buf, bytesRecv + 1, 0);//study send()
	}

	//close socket
	close(clientSocket);
}

int	main()
{
	try {
		createServer();
	} catch (std::exception &e) {
		std::cerr << "Exception caught! " << e.what() << std::endl;
	}

	return 0;
}
