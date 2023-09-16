#include "Server.hpp"

#include <string>

Server::Server() {
	this->password = "";
	this->port = 0;
}

Server::~Server() {
	// TODO: free alloc memory
}

std::string Server::getPassword() {
	return this->password;
}

int Server::getPort() {
	return this->port;
}

void Server::start(const int port, const std::string &password) {
	this->password = password.c_str();
	this->port = port;
}
