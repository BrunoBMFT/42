#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

//put colors in debugs
// the actual next thing i should do is manage to print stuff on client 1 that client 2 sent

int		main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << "Bad arguments" << std::endl;
		return 1;
	}
	try {
		Server srv(av[1], av[2]);
		srv.IRC();
	} catch (std::exception &e) {
		std::cerr << "Exception caught! " << e.what() << std::endl;//put this red
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
