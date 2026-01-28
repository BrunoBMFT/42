
void IrcServer::modeCommand(int client_fd, std::string restOfCommand)
{
	std::string modes = "itkol";
	std::istringstream iss(restOfCommand);
	std::vector<std::string> arguments;
	std::string argument;
	std::string msg = "MODE";
	while(iss >> argument)
		arguments.push_back(argument);
	if(arguments.empty())
	{
		sendClientMsg(client_fd, ERR_NEEDMOREPARAMS(msg));
		arguments.clear();
		return;
	}
	std::string channelName = arguments[0];
	std::transform(channelName.begin(), channelName.end(), channelName.begin(), ::tolower);
	if(channelName.empty())
	{
		sendClientMsg(client_fd, ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	Channel *channel = getChannelByName(channelName);
	channel = checkChannelName(channelName, _channels);
	if(!channel)
	{
		sendClientMsg(client_fd, ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	if(!channel->isOperator(client_fd))
	{
		if (channelName[0] && channelName[0] != '#' && channelName[0] != '&')
		{
			sendClientMsg(client_fd, ERR_BADCHANMASK(channelName));
			return;
		}
		else
		{
			sendClientMsg(client_fd, RPL_CHANNELMODEIS(channel->getName(), "+-", modes));
			return ;
		}
	}
	if(channelName[0] && channelName[0] != '#' && channelName[0] != '&')
	{
		sendClientMsg(client_fd, ERR_BADCHANMASK(channelName));
		return;
	}
	if(arguments.size() < 2 || arguments[1].empty())
	{
		sendClientMsg(client_fd, RPL_CHANNELMODEIS(channel->getName(), "+-", modes));
		arguments.clear();
		return;
	}

	bool positive = false;
	bool flag = false;
	size_t i = 0;
	size_t argIndex = 2;
	
	if(arguments[1][0] == '+' || arguments[1][0] != '-')
	{
		positive = true;
		if (arguments[1][0] == '+')
			i++;
		else
			flag = true;
	}
	else if (arguments[1][0] == '-')
		i++;
	for(; i < arguments[1].length(); i++)
	{
		if(arguments[1][i] != 'i' && arguments[1][i] != 't' && arguments[1][i] != 'k'
			&& arguments[1][i] != 'o' && arguments[1][i] != 'l' && arguments[1][i] != '+' && arguments[1][i] != '-')
		{
			sendClientMsg(client_fd, ERR_UNKNOWNMODE(arguments[1]));
			return;
		}
		
		switch (arguments[1][i])
		{
			case 'i': // i (Set/remove Invite-only channel)
				if(positive)
				{
					channel->setInviteOnly(true);
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " +i \r\n";
					sendClientMsg(client_fd, msg);
				}
				else
				{
					channel->setInviteOnly(false);
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " -i \r\n";
					sendClientMsg(client_fd, msg);
					positive = true;
				}
				break;
			case 't': // t (Set/remove the restrictions of the TOPIC command to channel operators)
				if(positive)
				{
					channel->setTopicProtection(true);
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " +t \r\n";
					sendClientMsg(client_fd, msg);
				}
				else
				{
					channel->setTopicProtection(false);
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " -t \r\n";
					sendClientMsg(client_fd, msg);
					positive = true;
				}
				break;
			case 'k': // k (Set/remove the channel key)
				if(positive)
				{
					if (argIndex < arguments.size())
					{
						channel->setPassword(arguments[argIndex]);
						msg = ":" + _user->getNick() + " MODE " + channel->getName() + " +k " + arguments[argIndex] + "\r\n";
						sendClientMsg(client_fd, msg);
						argIndex++; // Move to the next parameter
					}
					else
					{
						sendClientMsg(client_fd, ERR_NEEDMOREPARAMS(msg));
					}
				}
				else
				{
					channel->setPassword("");
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " -k \r\n";
					sendClientMsg(client_fd, msg);
					positive = true;
				}
				break;
			case 'o': // o (Set/remove channel operator)
				if(positive)
				{
					if (argIndex < arguments.size())
					{
						Client *targetUser = getUserByNick(arguments[argIndex]);
						if (targetUser)
						{
							if (targetUser->findChannel(channel->getName()) == -1)
							{
								sendClientMsg(client_fd, ERR_USERONCHANNEL(arguments[argIndex], channel->getName()));
								argIndex++; // Still move to next parameter
								continue;
							}
							
							channel->addOperator(targetUser);
							msg = ":" + _user->getNick() + " MODE " + channel->getName() + " +o " + arguments[argIndex] + "\r\n";
							
							for (size_t j = 0; j < channel->getUsers().size(); j++)
							{
								sendClientMsg(channel->getUsers()[j]->getFd(), msg);
							}
						}
						else
						{
							sendClientMsg(client_fd, ERR_NOSUCHNICK(arguments[argIndex]));
						}
						argIndex++; // Move to the next parameter
					}
					else
						sendClientMsg(client_fd, ERR_NEEDMOREPARAMS(msg));
				}
				else
				{
					if (argIndex < arguments.size())
					{
						Client *targetUser = getUserByNick(arguments[argIndex]);
						if (targetUser)
						{
							channel->removeOperator(targetUser);
							msg = ":" + _user->getNick() + " MODE " + channel->getName() + " -o " + arguments[argIndex] + "\r\n";
							sendClientMsg(client_fd, msg);
							for(size_t j = 0; j < channel->getUsers().size(); j++)
								sendClientMsg(channel->getUsers()[j]->getFd(), msg);
						}
						else
						{
							sendClientMsg(client_fd, ERR_NOSUCHNICK(arguments[argIndex]));
						}
						argIndex++; // Move to the next parameter
					}
					else
					{
						sendClientMsg(client_fd, ERR_NEEDMOREPARAMS(msg));
					}
				}
				break;
			case 'l': // l (Set/remove channel limit)
				if(positive)
				{
					if (argIndex < arguments.size())
					{
						channel->setLimit(atoi(arguments[argIndex].c_str()));
						msg = ":" + _user->getNick() + " MODE " + channel->getName() + " +l " + arguments[argIndex] + "\r\n";
						sendClientMsg(client_fd, msg);
						argIndex++; // Move to the next parameter
					}
					else
					{
						sendClientMsg(client_fd, ERR_NEEDMOREPARAMS(msg));
					}
				}
				else
				{
					channel->setLimit(0);
					msg = ":" + _user->getNick() + " MODE " + channel->getName() + " -l \r\n";
					sendClientMsg(client_fd, msg);
					positive = true;
				}
				break;
			case '+': // Handle changing mode from - to +
				positive = true;
				break;
			case '-': // Handle changing mode from + to -
				positive = false;
				break;
			default:
				break;
		}
	}
	arguments.clear();    
}