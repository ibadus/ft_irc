#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "socket.hpp"
#include "utils.hpp"
#include "signals.hpp"
#include "status.hpp" // global_status

#include <string>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <sys/epoll.h>

te_status global_status = e_STOP;

Server::Server(const unsigned int port, const std::string &password): _password(password.c_str()), _port(port), _socket_fd(0), _clients(std::vector<Client>(0)), _channels(std::vector<Channel>(0)) {
	this->_socket_fd = initSocket(this->_port);
	if (this->_socket_fd < 0)
		throw std::runtime_error("Could not start server.");
	this->_port = getPort(this->_socket_fd);
}

Server::~Server() {
	// TODO: free alloc memory
}


void Server::flush() {
	std::cout << TEXT_YELLOW << "Flushing..." << TEXT_RESET << std::endl;
	// TODO: warn connected users ?

	// TODO: clean epoll
	this->_epoll_fd < 0 ? close(this->_epoll_fd) : 0;
	this->_event_count = 0;

	// TODO: disconnect clients
	this->_clients.clear();
	// TODO: delete channels
	this->_channels.clear();
}

bool Server::initEpoll() {
	this->_epoll_fd = epoll_create1(0);
	if (this->_epoll_fd < 0) {
		std::cerr << "Error: epoll_create1 error" << std::endl;
		global_status = e_STOP;
		return false;
	}

	this->_event.events = EPOLLIN;
	this->_event.data.fd = this->_socket_fd;

	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, this->_socket_fd, &(this->_event))) {
		std::cerr << "Error: epoll_ctl error" << std::endl;
		global_status = e_STOP;
		return false;
	}

	return true;
}

bool Server::handlePolling() {
	this->_event_count = 0;

	while (global_status == e_RUN) {
		this->_event_count = epoll_wait(this->_epoll_fd, this->_events, EPOLL_MAX_EVENTS, -1);
		for (int i = 0; i < this->_event_count; i++) {
			if (this->_events[i].data.fd == this->_socket_fd && this->_events[i].events & EPOLLIN && global_status == e_RUN) {
				// TODO: handle new connection
			}
		}
	}

	return true;
}

void Server::start() {
	initAllSignalHandlers();

	global_status = e_RUN;
	while (global_status) {
		switch (global_status) {
			case e_RUN: {
				std::cout << TEXT_GREEN << "Server listening on port " << TEXT_BOLD << this->_port << TEXT_RESET << TEXT_GREEN << ", using password: " << TEXT_UNDERLINE << this->_password << TEXT_RESET << std::endl;

				if (!this->initEpoll())
					break;

				if (!this->handlePolling())
					break;

				break;
			}
			case e_RESTART: {
				std::cout << TEXT_YELLOW << "Server restarting..." << TEXT_RESET << std::endl;
				// TODO: send restart message to all clients
				global_status = e_RUN;

				break;
			}
			case e_STOP: {
				std::cout << TEXT_YELLOW << "Server stopping..." << TEXT_RESET << std::endl;
				// TODO: disconnect everyone

				break;
			}
		}
		this->flush();
	}

	std::cout << TEXT_YELLOW << "Server stopped, exiting..." << TEXT_RESET << std::endl;
	close(this->_socket_fd);
}
