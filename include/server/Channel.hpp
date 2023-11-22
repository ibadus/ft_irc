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
		std::set<std::string> getClientConnectList() const { return _clientConnected; };
		void	sendMessageToClients( std::string msg, std::string sender);

		bool 	getChannelPassw() { return this->_passwd; }
		void 	setChannelPassw(bool passw) { this->_passwd = passw; }

		bool 	getSizeLimit() { return this->_sizeLimit; }
		void 	setSizeLimit(bool size) { this->_sizeLimit = size; }

		bool 	getTopicLimitMode() { return this->_isTopicLimited; }
		void 	setTopicLimitMode(bool topicLimit) { this->_isTopicLimited = topicLimit; }

		bool 	getSizeLimitMode() { return this->_isSizeLimit; }
		void 	setSizeLimitMode(bool sizeLimit) { this->_isSizeLimit = sizeLimit; }

		bool 	getPasswMode() { return this->_isPasswordOnly; }
		void 	setPasswMode(bool passwordOnly) { this->_isPasswordOnly = passwordOnly; }
		
		bool 	getInviteMode() { return this->_isInviteOnly; }
		void 	setInviteMode(bool isInviteOnly) { this->_isInviteOnly = isInviteOnly; }

		std::set<std::string> getClientOperator() { return this->_clientOperators; }
		std::string getChannelName() const;
		std::string getTopic() const;
		void setTopic(std::string topic) { this->_topic = topic; }
		Server &getServer() const;
		Channel& operator=(const Channel& other);
		bool operator==(const Channel &other);
	private:
		Server&							_server;
		std::string						_name;
		std::string						_topic;
		size_t							_sizeLimit;
		std::string						_passwd;
		std::set<std::string>			_clientConnected; // ID is used to identify a client
		std::set<std::string>			_clientBanned; // ID is used to identify a client
		std::set<std::string>			_clientOperators; 
		bool							_isInviteOnly;
		bool							_isPasswordOnly;
		bool							_isSizeLimit;
		bool							_isTopicLimited;
};