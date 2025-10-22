#ifndef SERVER_HPP
# define SERVER_HPP
//divide these headers into each header
# include <iostream>
# include <sys/types.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <string>
# include <vector>
# include <poll.h>
# include <stdlib.h>//atoi
# include "Client.hpp"
#include "Colours.hpp"

class Server
{
	private:
		int				_port;//parameters
		std::string		_pass;//parameters

		int				_socket;
		sockaddr_in		server_addr;

		//pollfd for first in pfds
		pollfd			_srvPfd;
	public:
		//*CONSTRUCTORS
		Server(char *port, char *pass);

		//*GETTERS
		int		getSocket();
		int		getPort();
		std::string getPass();


		void	IRC();
};


#endif


