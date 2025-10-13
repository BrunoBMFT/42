#include "../includes/IRC.hpp"
//when saying study, learn the returns, what the functions can do, whatever else needed

void	IRC()
{
	//todo SERVER
	//create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);//*study socket, sockstream, AF_INET is IPv4
	if (listening == -1)
		throw (std::runtime_error("Cant create socket"));
	
	//bind the socket to IP / port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(6667);//study htons(), changed from 54000 to 6667
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);//study inet_pton()

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
		throw (std::runtime_error("Cant bind to IP/port"));

	//mark the socket for listening in
	if (listen(listening, SOMAXCONN) == -1)//study listen()
		throw (std::runtime_error("Cant listen"));
	//todo SERVER
	
	//todo CLIENT
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
	//todo CLIENT

	//while recieving message, echo the message


	//todo EXCHANGE
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
	//todo EXCHANGE

	//close socket
	close(clientSocket);
}

int		main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "Bad arguments" << std::endl;
		return 1;
	}
	try {
		IRC();
	} catch (std::exception &e) {
		std::cerr << "Exception caught! " << e.what() << std::endl;
	}

	return 0;
}
