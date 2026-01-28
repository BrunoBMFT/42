#include "../includes/Server.hpp"

bool	Server::isValidMode(int i, std::string args)
{
	if (!_clients[i].isRegistered())
		return (sendToClient(i, ERR_NOTREGISTERED(_clients[i].getNick())), false);
	if (args.empty())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")), false);
	return (true);
}

void	Server::outputMode(int i, int chId, bool enable, char mode, std::string args)
{
	char sign = (enable) ? '+' : '-';
	std::string strToSend = _clients[i].getPrefix() + " MODE " +  _channels[chId].getName() + " " + sign + mode + " " +args;
	channelBroadcast(chId, strToSend);
}

//todo ALL COMMANDS CAN PUT ENABLEMODE TO TRUE
//	std::cout << "mode: Invite, bool: " << enableMode << ", args: " << args[index] << std::endl;

void	Server::modeInviteOnly(int i, int chId, bool *enableMode)
{
	std::cout << "mode: Invite, bool: " << *enableMode << std::endl;
	_channels[chId].setInviteMode(*enableMode);
	// outputMode(i, chId, enableMode, 'i', "");
	if (*enableMode) {}
		// serverLog(_channels[chId].getName(), " is now invite only");
	else {
		// serverLog(_channels[chId].getName(), " is now NOT invite only");
		*enableMode = true;
	}
}

void	Server::modeTopicRestriction(int i, int chId, bool *enableMode)
{
	std::cout << "mode: Topic, bool: " << *enableMode << std::endl;
	_channels[chId].setTopicRestriction(*enableMode);
	// outputMode(i, chId, enableMode, 't', "");
	if (*enableMode) {}
		// serverLog(_channels[chId].getName(), " is now topic restricted");
	else {
		// serverLog(_channels[chId].getName(), " is now NOT topic restricted");
		*enableMode = true;
	}
}

void	Server::modeKey(int i, int chId, std::vector<std::string> args, bool *enableMode, int *argsIdx)
{
	if (!*enableMode) {
		std::cout << "mode: Key, bool: " << *enableMode << std::endl;
		_channels[chId].setChannelKey("");
		// outputMode(i, chId, enableMode, 'k', "");
		// serverLog(_channels[chId].getName(), " is now NOT key entry only");
		*enableMode = true;
		return ;
	}
	if (*argsIdx >= args.size())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")));
	std::cout << "mode: Key, bool: " << *enableMode << ", args: " << args[*argsIdx] << std::endl;
	_channels[chId].setChannelKey(args[*argsIdx]);
	*argsIdx++;
	// broadcastToJustThisClient
	// outputMode(i, chId, enableMode, 'k', key);
	// serverLog(_channels[chId].getName(), " is now key entry only :" + args[*argsIdx]);
}

void	Server::modeOp(int i, int chId, std::vector<std::string> args, bool *enableMode, int *argsIdx)
{
	if (*argsIdx >= args.size())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "MODE")));
	
	std::cout << "mode: Operator, bool: " << *enableMode << ", args: " << args[*argsIdx] << std::endl;
	int toOpId = getClientId(args[*argsIdx]);//if id == -1 ->	NOSUCHNICK?

	if (!isUserInChannel(toOpId, chId))
		return (sendToClient(i, ERR_USERNOTINCHANNEL(_clients[i].getNick(), args[*argsIdx], _channels[chId].getName())));
	
	if (_clients[i].getNick() == args[*argsIdx])
		return (sendToClient(i, "you cannot op yourself"));//maybe remove
	

	_channels[chId].setOp(toOpId, *enableMode);
	// outputMode(i, chId, enableMode, 'o', _clients[toOpId].getNick());
	// broadcastToAll
	if (*enableMode) {}
		// serverLog(args[*argsIdx], " is now op");
	else {
		// serverLog(args[*argsIdx], " is now NOT op");
		*enableMode = true;
	}
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
		std::cout << "mode: Limit, bool: " << *enableMode << std::endl;
		// outputMode(i, chId, limit, 'l', args[*argsIdx]);
		// serverLog(_channels[chId].getName(), "now has NO limit");
		*enableMode = true;
	}
	else {
		std::cout << "mode: Limit, bool: " << *enableMode << ", args: " << args[*argsIdx] << std::endl;
		// outputMode(i, chId, limit, 'l', args[*argsIdx]);
		// serverLog(_channels[chId].getName(), "now has limit of " + args[*argsIdx]);
	}
	*argsIdx++;
}


/*
	1. Create a list of all arguments
	2. Create a ArgIndex (starts at 2) -> only arguments[1] is +-ioltk, rest is arguments
	3. run for loop through arguments[1][i]
	4. everytime an argument is used, ArgIndex++
*/

void	Server::commandMode(int i, std::string line)
{
	if (!isValidMode(i, line))
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
	/* 
		if !isOp {
			if		args.size < 2		return channelModeIs
			else	ERR_NOPRIVILEGES
		}
	*/
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
				sendToClient(i, ERR_UMODEWUNKNOWNFLAG);//todo FIX OUTPUT
				break;
		}
	}
}