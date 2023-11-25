#include "Client.hpp"
#include "Server.hpp"
#include "utils.hpp"

#include <string>
#include <iostream>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event
#include <sys/socket.h> // send
#include <unistd.h> // close

size_t Client::g_ID = 0; // auto increment

Client::Client(int fd, Server &server, std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo): _fd(fd), _server(server), _host(host), _port(port), _conn_event(event), _addrinfo(addrinfo), _nickname(""), _client_msg(Message()), _operatorMode(false), _invisibleMode(true), _online(false) ,_registered(false), _identified(false) {
	Client::ID = Client::g_ID++;
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
	if (this != &other) {
        _fd = other.getFD();
		_host = other.getHost();
		_port = other.getPort();
		_server = other.getServer();
	}
    return *this;
}

bool Client::operator==(const Client &other)  {
	return this->_fd == other.getFD() && this->_host == other.getHost() && this->_port == other.getPort();
}

Client::~Client() {}

void Client::sendMsg(std::string msg) {
	std::cout << std::string(TEXT_BLUE) << "message send on --> " << this->getFD() << " : " << msg << std::string(TEXT_RESET) << std::endl;
	send(this->_fd, msg.c_str(), msg.length(), 0);
}


void Client::disconnect() {
	sendMsg(std::string(TEXT_RED) + "The server is disconnecting you..." + std::string(TEXT_RESET));
	//close(this->_fd);
	// std::cout << "Client (" << this->ID << ") disconnected." << std::endl;
}