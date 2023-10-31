#include "Client.hpp"
#include "utils.hpp"

#include <string>
#include <iostream>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event
#include <sys/socket.h> // send
#include <unistd.h> // close

size_t Client::g_ID = 0; // auto increment

Client::Client(int fd, std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo): _fd(fd), _host(host), _port(port), _conn_event(event), _addrinfo(addrinfo), _nickname(""), _registered(false), _identified(false) {
	Client::ID = Client::g_ID++;
}

Client::~Client() {}

void Client::sendMsg(std::string msg) {
	send(this->_fd, msg.c_str(), msg.length(), 0);
}

void Client::disconnect() {
	sendMsg(std::string(TEXT_RED) + "The server is disconnecting you..." + std::string(TEXT_RESET));
	close(this->_fd);
	std::cout << "Client (" << this->ID << ") disconnected." << std::endl;
}
