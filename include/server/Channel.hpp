#pragma once

#include "Server.hpp"
#include "../messages/Message.hpp"
#include <set>

class Server;

class Channel
{
	public:
		Channel(Server &server, std::string channel_name);
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
		bool 	getChannelMode() { return this->_isInviteOnly; }
		std::set<std::string> getClientOperator() { return this->_clientOperators; }
		std::string getChannelName() const;
		std::string getTopic() const;
		Server &getServer() const;
		Channel& operator=(const Channel& other);
		bool operator==(const Channel &other);
	private:
		Server&							_server;
		std::string						_name;
		std::string						_topic;
		std::set<std::string>			_clientConnected; // ID is used to identify a client
		std::set<std::string>			_clientBanned; // ID is used to identify a client
		std::set<std::string>			_clientOperators; 
		bool							_isInviteOnly;
};