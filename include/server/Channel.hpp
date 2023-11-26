#pragma once

#include "Server.hpp"
#include "../messages/Message.hpp"
#include <sstream>      // std::stringstream
#include <set>

class Server;

class Channel
{
	public:

		std::set<std::string>			clientConnected;
		std::set<std::string>			clientBanned;
		std::set<std::string>			clientOperators;
		std::set<std::string>			clientInvited;
		Channel(Server &server, std::string channel_name);
		~Channel( void );

		bool	isclientConnected(std::string ID);
		bool	isClientInvited(std::string ID);
		bool	isClientBanned(std::string ID);
		void	addClient(std::string ID);
		void	addBanned(std::string ID);
		void	addConnected(std::string ID);
		void	addOperator(std::string ID);
		void	addInvited(std::string ID);
		void	removeConnected(std::string ID);
		void	removeBanned(std::string ID);
		void	removeInvited(std::string ID);
		void	removeOperator(std::string ID);
		bool	isClientOperatorChannel(std::string ID);
		void	sendMessageToClients( std::string msg, std::string sender);

		std::string 	getChannelPassw() { return this->_passwd; }
		void 	setChannelPassw(std::string passw) { this->_passwd = passw; }

		size_t 	getSizeLimit() { return this->_sizeLimit; }
		void 	setSizeLimit(size_t size) { this->_sizeLimit = size; }

		bool 	getTopicLimitMode() { return this->_isTopicLimited; }
		void 	setTopicLimitMode(bool topicLimit) { this->_isTopicLimited = topicLimit; }

		bool 	getSizeLimitMode() { return this->_isSizeLimit; }
		void 	setSizeLimitMode(bool size) { this->_isSizeLimit = size; }

		bool 	getPasswMode() { return this->_isPasswordOnly; }
		void 	setPasswMode(bool passwordOnly) { this->_isPasswordOnly = passwordOnly; }
		
		bool 	getInviteMode() { return this->_isInviteOnly; }
		void 	setInviteMode(bool isInviteOnly) { this->_isInviteOnly = isInviteOnly; }
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
		bool							_isInviteOnly;
		bool							_isPasswordOnly;
		bool							_isSizeLimit;
		bool							_isTopicLimited;
};