#include "../includes/Server.hpp"

bool	Server::isValidTopic(int i, std::string args)
{
	if (!_clients[i].isRegistered())
		return (sendToClient(i, ERR_NOTREGISTERED(_clients[i].getNick())), false);
	if (args.empty())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "TOPIC")), false);
	return (true);
}

void	setTopicArgs(std::string line, std::string *chName, std::string *newTopic)
{
	size_t pos = line.find(' ');
	*chName = line.substr(0, pos);
	if (pos != std::string::npos) {
		std::string rest = line.substr(pos + 1);
		*newTopic = rest;
	}
	else
		*newTopic = "";
}

void	Server::noArgsTopic(int i, std::string chName)
{
	int chId = getChannelId(chName);
	if (_channels[chId].getTopic().empty() || _channels[chId].getTopic() == ":")
		return (sendToClient(i, RPL_NOTOPIC(getServerName(), _clients[i].getNick(), chName)));
	sendToClient(i, RPL_TOPIC(getServerName(), _clients[i].getNick(), chName, _channels[chId].getTopic()));
	sendToClient(i, RPL_TOPICWHOTIME(getServerName(), _clients[i].getPrefix(), chName, _channels[chId].getTopicAuthor(), _channels[chId].getTopicTimeSet()));
}

void	Server::commandTopic(int i, std::string args)
{
	if (!isValidTopic(i, args))
		return ;

		std::string chName, newTopic;
	setTopicArgs(args, &chName, &newTopic);

	int chId = getChannelId(chName);
	if (!isUserInChannel(i, chId))
		return (sendToClient(i, ERR_NOTONCHANNEL(_clients[i].getNick(), chName)));
	if (newTopic.empty())
		return (noArgsTopic(i, chName));
	if (_channels[chId].isTopicRestricted() && !_channels[chId].isOp(i))
		return (sendToClient(i, ERR_CHANOPRIVSNEEDED(_clients[i].getNick(), chName)));
	
	//TODO taking out the : of the new topic if it exists //debug line
	_channels[chId].setTopic(newTopic);
	_channels[chId].setTopicAuthor(_clients[i].getPrefix());
	_channels[chId].setTopicTimeSet();
	//instead of getNick, use getPrefix
	//channelBroadcast(chId, RPL_TOPIC(_clients[i].getNick(), chName, newTopic)); //debug line
	channelBroadcast(chId, _clients[i].getPrefix() + " TOPIC " + chName + " :" + newTopic.substr(1) + "\r\n");
}