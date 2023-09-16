#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include "status.hpp" // global_status

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>

te_status global_status = e_STOP;

Server::Server(const unsigned int port, const std::string &password): _password(password.c_str()), _port(port), _fd(0), _clients(std::vector<Client>(0)), _channels(std::vector<Channel>(0)) { }

Server::~Server() {
	// TODO: free alloc memory
}

std::string Server::getPassword() {
	return this->_password;
}

int Server::getPort() {
	return this->_port;
}


void Server::flush() {
	std::cout << TEXT_YELLOW << "Flushing..." << TEXT_RESET << std::endl;
	// TODO: warn connected users ?

	// TODO: disconnect clients
	this->_clients.clear();
	// TODO: delete channels
	this->_channels.clear();
}

void Server::start(const int fd) {
	this->_fd = fd;

	global_status = e_RUN;
	while (global_status) {
		switch (global_status) {
			case e_RUN: {
				std::cout << TEXT_GREEN << "Server listening on port " << TEXT_BOLD << this->_port << TEXT_RESET << TEXT_GREEN << ", using as password: " << TEXT_UNDERLINE << this->_password << TEXT_RESET << std::endl;
				
				// TODO: clean code
				// init epoll
				int epoll_fd = epoll_create1(0);
				if (epoll_fd < 0) {
					std::cerr << "Error: epoll_create1 error" << std::endl;
					global_status = e_STOP;
				}

				struct epoll_event event, events[EPOLL_MAX_EVENTS];
				event.events = EPOLLIN;
				event.data.fd = fd;

				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event)) {
					std::cerr << "Error: epoll_ctl error" << std::endl;
					global_status = e_STOP;
				}

				int event_count = 0;
				while (global_status == e_RUN) {
					// TODO: do the magic stuff
					event_count = epoll_wait(epoll_fd, events, EPOLL_MAX_EVENTS, -1);
					for (int i = 0; i < event_count; i++) {
						if (events[i].data.fd == fd && events[i].events & EPOLLIN && global_status == e_RUN) {
							// TODO: handle new connection
						}
					}
				}

				epoll_fd < 0 ? close(epoll_fd) : 0;
				break;
			}
			case e_RESTART: {
				std::cout << TEXT_YELLOW << "Server restarting..." << TEXT_RESET << std::endl;
				// TODO: restart
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
	close(fd); // close the socket
}
