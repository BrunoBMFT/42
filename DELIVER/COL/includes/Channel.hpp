#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Utils.hpp"
/**
 * Changed by adding topicTimeSet to store the time when topic was set
 * and topicSetter to store who set the topic
 * then i made the correspondig get and setter functions
 */
class Channel
{
	private:
		static int			_globalChannelId;
		int					_id;
		std::string			_name;
		std::string			_channelKey;
		int				    _limit;
		std::string			_topic;
		std::string 		_topicTimeSet;
		std::string			_topicSetter;
		bool				_isInviteOnly;
		bool				_isTopicRestricted;
		std::vector<int>	_clientsInChannel;
		std::vector<int>	_ops;
	public:
		Channel(std::string name);
		Channel();
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		~Channel();
		

		std::string		getTopicTimeSet();
		std::string		getTopicSetter();
		int				getId();
		std::string		getName();
		std::string		getChannelKey();
		std::string		getTopic();
		bool			isInviteOnly();
		bool 			isTopicRestricted();
		size_t			getLimit();
		std::vector<int> &getClientsInChannel();
		bool			isOp(int id);
		
		void			setTopicTimeSet();
		void			setTopicSetter(std::string setter);
		void			setId(int id);
		void			setName(std::string name);
		void			setChannelKey(std::string key);
		void			setTopic(std::string topic);
		void			setInviteMode(bool value);
		void			setTopicRestriction(bool value);
		void			setLimit(int limit);
		void			setOp(int id, bool opOrNot);
		void			decrementId();
		
		void	addClient(int id);
		void	removeClient(int id);
};

#endif