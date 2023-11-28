#include "Client.hpp"
#include "Server.hpp"
#include "utils.hpp"

#include <string>
#include <iostream>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event
#include <sys/socket.h> // send
#include <unistd.h> // close
#include <ctime>


Client::Client(int fd, Server &server, std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo): _fd(fd), _server(server), _host(host), _port(port), _conn_event(event), _addrinfo(addrinfo), _nickname(""), _client_msg(Message()), _operatorMode(false), _invisibleMode(true), _online(false) ,_registered(false), _identified(false) {
	this->ID = "";
	this->lastPingSent = time(0);
	this->lastPongReceived = time(0);
}

std::string Client::getPreviousNick () 
{
	if (this->_nick_history.empty())
		return ("");
	if (this->_nick_history.size() < 2)
		return (this->_nick_history[this->_nick_history.size() - 1]);
	return (this->_nick_history[this->_nick_history.size() - 2]);
}

Client& Client::operator=(const Client& other) {

	 if (this != &other) 
	 {
        this->_fd = other._fd;
        this->_server = other._server;
        this->ID = other.ID;
        this->recv_buffer = other.recv_buffer;
        this->lastPingSent = other.lastPingSent;
        this->lastPongReceived = other.lastPongReceived;
        this->_host = other._host;
        this->_port = other._port;
        this->_conn_event = other._conn_event;
        this->_addrinfo = other._addrinfo;
        this->_nick_history = other._nick_history;
        this->_nickname = other._nickname;
        this->_username = other._username;
        this->_realname = other._realname;
        this->_client_msg = other._client_msg;
        this->_operatorMode = other._operatorMode;
        this->_invisibleMode = other._invisibleMode;
        this->_online = other._online;
        this->_hasNickName = other._hasNickName;
        this->_registered = other._registered;
        this->_identified = other._identified;
    }
    return *this;
}


void	Client::ping()
{
	this->sendMsg("PING " + this->_server.getServerName() + "\r\n" );;
}

Client::~Client() {}

void Client::sendMsg(std::string msg) {
	std::cout << std::string(TEXT_BLUE) << "message send on --> " << this->getFD() << " : " << msg << std::string(TEXT_RESET) << std::endl;
	send(this->_fd, msg.c_str(), msg.length(), 0);
}


void Client::disconnect() {
	sendMsg(std::string(TEXT_RED) + "The server is disconnecting you..." + std::string(TEXT_RESET));
}