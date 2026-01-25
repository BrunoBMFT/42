#include "../includes/Server.hpp"

/**
 * @brief Validates the TOPIC command arguments before execution.
 * 
 * Performs basic validation to ensure the client is registered
 * and that arguments were provided.
 * 
 * @param i    The file descriptor index of the client sending the command.
 * @param args The raw arguments: "<channel> [<topic>]".
 * 
 * @return true if basic validation passes.
 * @return false if validation fails (error sent to client).
 * 
 * @note Sends ERR_NOTREGISTERED (451) if client is not registered.
 * @note Sends ERR_NEEDMOREPARAMS (461) if no arguments provided.
 */
bool	Server::isValidTopic(int i, std::string args)
{
	if (!_clients[i].isRegistered())
		return (sendToClient(i, ERR_NOTREGISTERED(_clients[i].getNick())), false);
	if (args.empty())
		return (sendToClient(i, ERR_NEEDMOREPARAMS(_clients[i].getNick(), "TOPIC")), false);
	return (true);
}

/**
 * @brief Parses the TOPIC command arguments into channel name and new topic.
 * 
 * Splits the input line at the first space character to extract the
 * channel name and, if present, the new topic.
 * 
 * @param line      The raw arguments string: "<channel> [<topic>]".
 * @param channel   Pointer to store the extracted channel name.
 * @param newTopic  Pointer to store the extracted new topic (empty if not provided).
 * 
 * @note If no space is found, the entire line is treated as the channel name.
 */
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

/**
 * @brief Sends the topic setter and time information for a channel to a client.
 *
 * This function replies to the client with the IRC numeric RPL_TOPICWHOTIME (333),
 * which includes information about who set the channel topic and when it was set.
 * This is typically sent after the topic itself (RPL_TOPIC/332) in response to a TOPIC query.
 *
 * @param i      The file descriptor index of the client requesting the information.
 * @param chName The name of the channel whose topic time and setter are being reported.
 *
 * @note The function assumes that the channel exists and that topic setter/time
 *       information is stored in the channel object.
 * @note The reply format is:
 *       :<server> 333 <nick> <channel> <topic-setter> <unix-time>
 */
void	Server::sendTopicTime(int i, std::string chName)
{
	int chId = getChannelId(chName);
	//TODO implement topic time storage and sending
	/* (void)i;
	(void)chId; */
	//time_t timestamp = time(&timestamp);
	//char  *dt = ctime(&timestamp);
	/* std::stringstream ss;
	ss << timestamp;
	std::string ts = ss.str(); */
	//struct tm datetime = *localtime(&timestamp);
	/* std::string timeStr = (datetime.tm_year + 1900) + "-" +
						  (datetime.tm_mon + 1) + "-" +
						  (datetime.tm_mday) + " " +
						  (datetime.tm_hour) + ":" +
						  (datetime.tm_min) + ":" +
						  (datetime.tm_sec); */
	std::cout << "Topic set on: " << _channels[chId].getTopicTimeSet() << std::endl;
	sendToClient(i, RPL_TOPICWHOTIME(getServerName(), _clients[i].getPrefix(), chName, _channels[chId].getTopicSetter(), _channels[chId].getTopicTimeSet()));
	//sendToClient(i, RPL_TOPICTIME(...));
}

/**
 * @brief Handles the TOPIC command when no new topic is provided.
 * 
 * Retrieves and sends the current topic of the specified channel
 * to the requesting client. If no topic is set, notifies the client accordingly.
 * 
 * @param i      The file descriptor index of the client requesting the topic.
 * @param chName The name of the channel whose topic is requested.
 * 
 * @note Sends RPL_NOTOPIC (331) if no topic is set for the channel.
 * @note Sends RPL_TOPIC (332) with the current topic if it exists.
 * @note Sends RPL_TOPIC (333) through sendTopicTime() with the topic set time and topic setter if it exists.
 */
void	Server::noArgsTopic(int i, std::string chName)
{
	int chId = getChannelId(chName);
	//std::cout << "TOPIC: " << "[" <<_channels[chId].getTopic() << "]" << std::endl; //debug line
	if (_channels[chId].getTopic().empty() || _channels[chId].getTopic() == ":")
		return (sendToClient(i, RPL_NOTOPIC(getServerName(), _clients[i].getNick(), chName)));
	/**
	 * Changed here by including the sendTopicTime function
	 * and switching plaves with sendToClient (because we first need to send the topic then the time
	 * from what I saw in the hexhat client)
	 */
	sendToClient(i, RPL_TOPIC(getServerName(), _clients[i].getNick(), chName, _channels[chId].getTopic()));
	return (sendTopicTime(i, chName));
	//return (sendToClient(i, ":MyIRC 332 " + _clients[i].getNick() + " " + chName + " " + _channels[chId].getTopic() + "\r\n")); // debug line
}

/**
 * @brief Handles the IRC TOPIC command to set or get a channel's topic.
 * 
 * Validates the command, checks permissions, and if successful,
 * sets a new topic for the specified channel or retrieves the current topic.
 * 
 * @param i    The file descriptor index of the client sending the command.
 * @param args The raw arguments: "<channel> [<topic>]".
 * 
 * @note If no topic is provided, calls noArgsTopic() to send the current topic./kick
 * @note Sends ERR_NOTONCHANNEL (442) if the client is not on the channel.
 * @note Sends ERR_CHANOPRIVSNEEDED (482) if topic is restricted and client is not an operator.
 */
void	Server::commandTopic(int i, std::string args)
{
	//std::cout << "FIRST" << std::endl; removed debug line
	if (!isValidTopic(i, args))
		return ;
	//std::cout << "SECOND" << std::endl; removed debug line
	std::string chName, newTopic;
	setTopicArgs(args, &chName, &newTopic);
	//std::cout << "THIRD" << std::endl; removed debug line
	//std::cout << "ARGS: " << args << std::endl; //debug line
	//std::cout << "CHNAME: " << chName << " NEWTOPIC: " << newTopic << std::endl; //debug line
	int chId = getChannelId(chName);
	if (!isUserInChannel(i, chId))
		return (sendToClient(i, ERR_NOTONCHANNEL(_clients[i].getNick(), chName)));
	if (newTopic.empty())
		return (noArgsTopic(i, chName));
	if (_channels[chId].isTopicRestricted() && !_channels[chId].isOp(i))
		return (sendToClient(i, ERR_CHANOPRIVSNEEDED(_clients[i].getNick(), chName)));
	//TODO taking out the : of the new topic if it exists //debug line
	//std::cout << "FOURTH" << std::endl; removed debug line
	//std::string oldTopic = _channels[chId].getTopic(); //removed debug line
	//std::cout << "Setting topic for channel " << chName << " to: " << newTopic << std::endl;
	_channels[chId].setTopic(newTopic);
	_channels[chId].setTopicSetter(_clients[i].getPrefix());
	_channels[chId].setTopicTimeSet();
	/**
	 * Changed broadcast to match IRC protocol format:
	 * From what I understood the hexchat needs to get a Prefix + " TOPIC <channel> :<new topic>\r\n"
	 * and since the message you sent wasnt exatcly following that format it wasnt displaying the topic change
	 * on the client side.
	 */
	//channelBroadcast(chId, RPL_TOPIC(_clients[i].getNick(), chName, newTopic)); //debug line
	channelBroadcast(chId, _clients[i].getPrefix() + " TOPIC " + chName + " :" + newTopic.substr(1) + "\r\n");
	//std::cout << "Topic for channel " << oldTopic << " set to: " << _channels[chId].getTopic() << std::endl; //removed debug line
	//std::cout << "FIFTH" << std::endl; removed debug line
}