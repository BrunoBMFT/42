#include "../includes/Server.hpp"

bool	Server::isValidMode(int i, std::string args)
{
	if (!_clients[i].isRegistered())
		return (sendToClient(i, ERR_NOTREGISTERED(_clients[i].getNick())), false);
	if (args.empty())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")), false);
	return (true);
}

// void	Server::outputMode(int i, int chId, bool enable, char mode, std::string args)
// {
// 	char sign = (enable) ? '+' : '-';
// 	std::string strToSend = _clients[i].getPrefix() + " MODE " +  _channels[chId].getName() + " " + sign + mode + " " +args;
// 	channelBroadcast(chId, strToSend);
// }

//!TEST USING ALL COMMANDS POSITIVE AND NEGATIVE AND POSITIVE TO SEE ITS ALRIGHT
//todo Check which ones broadcast to channel or to client

void	testOutput(std::string mode, bool enable, std::vector<std::string> args, int index) {
	std::cout << (enable ? '+' : '-') << "mode: " << mode /*<< ", bool: " << (enable ? '+' : '-')*/;
	if (!args.empty())
		std::cout << ", args: " << args[index] << std::endl;
}

void	Server::modeInviteOnly(int i, int chId, bool *enableMode)
{
	//todo testing
	testOutput("Invite", enableMode, std::vector<std::string>(NULL), 0);
	_channels[chId].setInviteMode(*enableMode);
	// outputMode(i, chId, enableMode, 'i', "");
	if (!*enableMode)
		*enableMode = true;
}

void	Server::modeTopicRestriction(int i, int chId, bool *enableMode)
{
	//todo testing
	testOutput("Topic", *enableMode, std::vector<std::string>(NULL), 0);
	_channels[chId].setTopicRestriction(*enableMode);
	// outputMode(i, chId, enableMode, 't', "");
	if (!*enableMode)
		*enableMode = true;
}

void	Server::modeKey(int i, int chId, std::vector<std::string> args, bool *enableMode, int *argsIdx)
{
	if (!*enableMode) {
	//todo testing
		testOutput("Key", *enableMode, std::vector<std::string>(NULL), 0);
		_channels[chId].setChannelKey("");
		*enableMode = true;
		return ;
	}
	if (*argsIdx >= args.size())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")));
	//todo testing
	testOutput("Key", enableMode, args, *argsIdx);
	_channels[chId].setChannelKey(args[*argsIdx]);
	*argsIdx++;
}

void	Server::modeOp(int i, int chId, std::vector<std::string> args, bool *enableMode, int *argsIdx)
{
	//todo testing
	testOutput("Operator", enableMode, args, *argsIdx);
	if (*argsIdx >= args.size())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")));

	int toOpId = getClientId(args[*argsIdx]);//if id == -1 ->	NOSUCHNICK?

	if (!isUserInChannel(toOpId, chId))
		return (sendToClient(i, ERR_USERNOTINCHANNEL(_clients[i].getNick(), args[*argsIdx], _channels[chId].getName())));
	
	if (_clients[i].getNick() == args[*argsIdx])
		return (sendToClient(i, "you cannot op yourself"));//maybe remove
	
	_channels[chId].setOp(toOpId, *enableMode);

	if (!*enableMode)
		*enableMode = true;
	*argsIdx++;
}

void	Server::modeLim(int i, int chId, std::vector<std::string> args, bool *enableMode, int *argsIdx)
{
	int limit;
	if (!*enableMode)//todo || !enableMode
		limit = 0;
	// else if (!isNum(args[*argsIdx]))
	// 	return (*argsIdx++, sendToClient(i, args[*argsIdx] + " is not a number"));
	else if (*argsIdx >= args.size())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")));
	else
		limit = atoi(args[*argsIdx].c_str());
	
	_channels[chId].setLimit(limit);
	if (limit == 0) {//todo || !enableMode
		testOutput("Limit", *enableMode, std::vector<std::string>(NULL), 0);
		*enableMode = true;
	}
	else {
		//todo testing
		testOutput("Limit", enableMode, args, *argsIdx);
	}
	*argsIdx++;
}

void	Server::commandMode(int i, std::string line)
{
	if (!isValidMode(i, line))//name this parseAndSet(), and put every if in it
		return ;

	std::vector<std::string> args = getArgs(line);
	std::cout << "OUTPUTTING MODE ARGUMENTS\n";
	for (size_t j = 0; j < args.size(); j++) 
		std::cout << "Argument: " << j << ": [" << args[j] << "]\n";
	
	int chId = getChannelId(args[0]);
	if (!isUserInChannel(i, chId))
		return (sendToClient(i, ERR_NOTONCHANNEL(_clients[i].getNick(), args[0])));
	if (args.size() < 2)
		return (sendToClient(i, RPL_CHANNELMODEIS(_clients[i].getNick(), args[0])));
	if (_channels[chId].isOp(i))
		return (sendToClient(i, ERR_NOPRIVILEGES(_clients[i].getNick())));
	
	size_t j = 0;
	int		argIdx = 2;
	bool	enableMode = (args[1][0] != '-');
	if (args[1][0] == '+' || args[1][0] == '-')
		j++;
	
	for (; j < args[1].length(); j++) {
		switch (args[1][j]) {
			case 'i':
				modeInviteOnly(i, chId, &enableMode);
				break ;
			case 't':
				modeTopicRestriction(i, chId, &enableMode);
				break ;
			case 'k':
				modeKey(i, chId, args, &enableMode, &argIdx);
				break ;
			case 'o':
				modeOp(i, chId, args, &enableMode, &argIdx);
				break ;
			case 'l':
				modeLim(i, chId, args, &enableMode, &argIdx);
				break ;
			case '+':
				enableMode = true;
				break ;
			case '-':
				enableMode = false;
				break ;
			default:
				sendToClient(i, ERR_UMODEWUNKNOWNFLAG);//todo FIX OUTPUT to also have flag
				break;
		}
	}
}