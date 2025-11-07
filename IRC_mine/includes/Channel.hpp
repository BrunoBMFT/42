#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "Client.hpp"
# include "Colours.hpp"
# include "Server.hpp"

//todo I NEED TO BE SURE TO REMOVE CLIENTS THAT CLOSED SOCKET FROM THIS VECTOR
class Channel
{
	private:
		static int			_globalChannelId;
		int					_id;
		std::string			_name;

		std::vector<int>	_clientsInChannel;
	public:
		Channel(std::string name) {
			_id = _globalChannelId++;
			_name = name;
		}
		
		std::vector<int> getClientsInChannel() {
			return (_clientsInChannel);
		}

		//todo hardcoded
		void	clientJoin(int id) {
			_clientsInChannel.push_back(id);

			//todo this is testing
			std::cout << "Clients in Channel temp: ";
			for (std::vector<int>::iterator it = _clientsInChannel.begin(); it != _clientsInChannel.end(); it++)
			{
				std::cout << *it << ", ";
			}
			std::cout << std::endl;
		}
		int			getId() { return (_id); }

};

#endif