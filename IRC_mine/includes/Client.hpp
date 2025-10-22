#ifndef CLIENT_HPP
# define CLIENT_HPP
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
# include "Colours.hpp"


//todo when setting username and nick, have the setUser and setNick do the parsing
class Client
{
	private:
		static int	_globalId;
		int			_id;

		int			_socket;
		pollfd		_pfd;

	public:
		//*CONSTRUCTORS
		Client(int srvSocket);

		//*GETTERS
		int		getId();
		int		getSocket();
		pollfd	&getPfd();//why &


};


#endif


