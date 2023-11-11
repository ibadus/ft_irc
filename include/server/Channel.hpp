#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>
# include <poll.h>
# include <vector>
# include <map>
# include <set>
# include "server.hpp"
# include "./client/client.hpp"



// Channel start with '&', '#', '+' or '!'
// length max 50 charact
// this char is not allowed ' ', control G (^G / ASCII 7) or coma (',')
// not sensible case
class Channel
{

	public:
		Channel( Server& server, std::string channel_name );
		~Channel( void );

		bool	isclientConnected(std::string ID);
		bool	isClientBanned(std::string ID);
		void	addClient(std::string ID);
		void	addOperator(std::string ID);
		void	removeConnected(std::string ID);
		void	removeBanned(std::string ID);
		void	removeOperator(std::string ID);
		bool	isClientOperatorChannel(std::string ID);
		void	sendMessageToClients( std::string msg, std::string sender);
		std::string getChannelName() const { return this->_name; }
		std::string getTopic() const { return this->_topic; }
	private:
		Server&							_server;
		std::string						_name;
		std::string						_topic;
		std::set<std::string>			_clientConnected; // ID is used to identify a client
		std::set<std::string>			_clientBanned; // ID is used to identify a client
		std::set<std::string>			_clientOperators; 
		bool							_isInviteOnly;
};

#endif