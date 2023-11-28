#pragma once

#include "Server.hpp"
#include "../messages/Message.hpp"
#include <string>
#include <ctime>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event

class Server;

class Client
{
	public:
		std::string ID;
		std::string recv_buffer;
		time_t						lastPingSent;
		time_t						lastPongReceived;
		Client(int fd, Server &server ,std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo);
		~Client();

		Client& operator=(const Client& other);
		int getFD() const { return this->_fd; }
		void setID(std::string id) { this->ID = id; }
		std::string getID() const { return this->ID; }
		std::string getIDCMD() const { return (":" + this->ID); }
		std::string getHost() const { return this->_host; }
		int getPort() const { return this->_port; }
		Message getClientMessage() const  { return this->_client_msg; }
		void setClientMessage(Message message) { this->_client_msg = message; }
		const Server &getServer() const { return this->_server; }
		struct epoll_event getEvent() const { return this->_conn_event; }
		struct sockaddr_in getAddrinfo() const { return this->_addrinfo; }
		std::string getNickname() const { return this->_nickname; }
		void setNickname(std::string nickname) { this->_nickname = nickname; }
		std::string getUserName() const { return this->_username; }
		void setUserName(std::string username) { this->_username = username; }
		std::string getRealName() const { return this->_realname; }
		void setRealName(std::string realname) { this->_realname = realname; }
		std::string getPreviousNick ();
		void setNickHistory(std::string nickname) { this->_nick_history.push_back(nickname); }
		void sendMsg(std::string msg);
		void ping();
		void disconnect();

		bool isRegistered() const { return this->_registered; }
		void setRegistered(bool registered) { this->_registered = registered; }

		bool isOnline() const {return this->_online; }
		void setOnline(bool online)  { this->_online = online; }
	
		bool isIdentified() const { return this->_identified; }
		void setIdentified(bool identified) { this->_identified = identified; }
	
		bool getHasNick() const { return this->_hasNickName; }
		void setHasNick(bool nick)  { this->_hasNickName = nick;}

		bool isOperatorMode() const { return this->_operatorMode; }
		void setOperatorMode(bool isOp) { this->_operatorMode = isOp; }

		bool isInvisibleMode() const { return this->_invisibleMode; }
		void setInvisibleMode(bool invisible ) { this->_invisibleMode = invisible; }
		Server &getServer() { return this->_server; }
 
	private:

		int _fd;
		Server &_server;
		std::string _host;
		int _port;

		struct epoll_event _conn_event;
		struct sockaddr_in 	_addrinfo;
		std::vector<std::string> _nick_history;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		Message _client_msg;

		bool _operatorMode;
		bool _invisibleMode;
		bool _online;
		bool _hasNickName;
		bool _registered;
		bool _identified;
		
};