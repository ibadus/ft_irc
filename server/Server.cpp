#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "socket.hpp"
#include "utils.hpp"
#include "signals.hpp"
#include "status.hpp" // global_status
#include "commands.hpp"
#include "Message.hpp"

#include <string>
#include <iostream>
#include <exception>
#include <unistd.h> // close
#include <sys/epoll.h>
#include <sys/socket.h> // accept
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_ntoa
#include <fcntl.h> // fcntl

te_status global_status = e_STOP;

Server::Server(const std::string &name, const unsigned int port, const std::string &password): _name(name.c_str()), _password(password.c_str()), _port(port), _socket_fd(0), _events(std::vector<struct epoll_event>(EPOLL_MAX_EVENTS)) {
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
	// TODO: clean epoll
	this->_epoll_fd < 0 ? close(this->_epoll_fd) : 0;
	this->_event_count = 0;
	this->disconnectAllClients();
	// TODO: delete channels
	this->_channels.clear();
}

void Server::disconnectClient(const int fd) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getFD() == fd) {
			it->disconnect();
			this->_clients.erase(it);
			break;
		}
	}
}

void Server::disconnectAllClients() {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		it->disconnect();
	}
	this->_clients.clear();
}

void Server::sendMsgToAll(std::string msg) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		it->sendMsg(msg);
	}
}

Client &Server::getClientByFD(const int fd) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getFD() == fd) {
			return *it;
		}
	}
	return *this->_clients.end();
}


Client &Server::getClient(std::string ID)
{
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getID() == ID) {
			return *it;
		}
	}
	return *this->_clients.end();
}

bool Server::initEpoll() {
	this->_epoll_fd = epoll_create1(0);
	if (this->_epoll_fd < 0) {
		std::cerr << "Error: epoll_create1 error" << std::endl;
		global_status = e_STOP;
		return false;
	}

	// set non blocking
	if (fcntl(this->_epoll_fd, F_SETFL, O_NONBLOCK) < 0) {
		close(this->_epoll_fd);
		std::cerr << "Error: setting epoll non blocking" << std::endl;
		global_status = e_STOP;
		return -1;
	}

	this->_event.events = EPOLLIN;
	this->_event.data.fd = this->_socket_fd;

	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, this->_socket_fd, &(_event)) < 0) {
		close(this->_epoll_fd); // close socket
		std::cerr << "Error: epoll_ctl error" << std::endl;
		global_status = e_STOP;
		return false;
	}
	return true;
}

bool Server::handlePolling() {
	this->_event_count = 0;

	while (global_status == e_RUN) {
		std::cout << "[DEBUG] epoll_wait, max events: " << static_cast<int>(this->_events.size()) << std::endl; // TODO: remove
		this->_event_count = epoll_wait(this->_epoll_fd, this->_events.data(), static_cast<int>(this->_events.size()), -1);
		if (this->_event_count < 0) {
			std::cerr << "Error: epoll_wait error" << std::endl;
			global_status = e_STOP;
			return false;
		}

		// if we are hitting the events limit, resize it; even without resizing, the subsequent
		// calls would round-robin through the remaining ready sockets, but it's better to give
		// the call enough room once we start hitting the boundary
		if (this->_event_count >= static_cast<int>(this->_events.size()))
			this->_events.resize(this->_events.size() * 2);

		std::cout << "[DEBUG] event_count: " << this->_event_count << std::endl; // TODO: remove

		for (int i = 0; i < this->_event_count; i++) {
			// TODO: if ptr is defined on new connection and not after then use 'if (_events[i].data.ptr)' instead of 'if (this->_events[i].data.fd == this->_socket_fd)' below
			// check line poco/PollSet.cpp:205
			std::cout << "[DEBUG] event: ptr=" << this->_events[i].data.ptr << " | fd=" << this->_events[i].data.fd << " | u32=" << this->_events[i].data.u32 << " | u64=" << this->_events[i].data.u64 << " | events=" << this->_events[i].events << " (EPOLLIN=" << EPOLLIN << ")" << std::endl; // TODO: remove
			if (global_status == e_RUN) {
				if (this->_events[i].data.fd == this->_socket_fd && this->_events[i].events & EPOLLIN) {
					this->handleNewConnection(this->_events[i]);
				} else if (this->_events[i].events & EPOLLIN) {
					this->handleMessages(this->_events[i].data.fd);
					continue;
				} else if (this->_events[i].events & EPOLLERR || this->_events[i].events & EPOLLHUP || this->_events[i].events & EPOLLHUP) {
					std::cerr << TEXT_RED << "Error: Connection Client fd: " << this->_events[i].data.fd << " closed" << TEXT_RESET << std::endl;
					epoll_ctl(this->_epoll_fd, EPOLL_CTL_DEL, this->_events[i].data.fd, NULL);
					this->disconnectClient(this->_events[i].data.fd);
					close(this->_events[i].data.fd);
					continue;
				} else {
					if (this->_events[i].events == EPOLLERR)
						std::cerr << TEXT_YELLOW << "Error: event EPOLLERR, continuing..." << TEXT_RESET << std::endl;
					else
						std::cerr << TEXT_YELLOW << "Error: event '" << this->_events[i].events << "' (unknown), continuing..." << TEXT_RESET << std::endl;
					continue;
				}
			}
		}
	}
	return true;
}

bool Server::handleNewConnection(struct epoll_event &event) {
	struct sockaddr_in client_addr; 
	socklen_t client_addr_len = sizeof(client_addr);

	int client_fd = accept(this->_socket_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
	if (client_fd < 0) {
		std::cerr << "Error: Failed to accept new connection" << std::endl;
		return false;
	}

	if (this->_clients.size() >= MAX_CLIENTS) {
		std::cerr << "Error: Max clients reached" << std::endl;
		close(client_fd);
		return false;
	}

	int flags = fcntl(client_fd, F_GETFL, 0);
	if (flags < 0) {
		std::cerr << "Error: Failed to get socket flags" << std::endl;
		close(client_fd);
		return false;
	}
	flags |= O_NONBLOCK;
	// set non-blocking socket as we set it to edge to avoid infinite block on next epoll_wait()
	// (see 'Level-triggered and edge-triggered' section at: https://man7.org/linux/man-pages/man7/epoll.7.html) 
	if (fcntl(client_fd, F_SETFL, flags) < 0) {
		std::cerr << "Error: Failed to set non-blocking socket" << std::endl;
		close(client_fd);
		return false;
	}

	struct epoll_event client_event;
	client_event.events =  EPOLLIN | EPOLLRDHUP;
	client_event.data.fd = client_fd;
	// add client to epoll for performance reasons
	// (see example at: https://man7.org/linux/man-pages/man7/epoll.7.html)
	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) < 0) {
		std::cerr << "Error: Failed to set non-blocking socket" << std::endl;
		close(client_fd);
		return false;
	}

	Client client(client_fd, *this, std::string(inet_ntoa(client_addr.sin_addr)), static_cast<int>(client_addr.sin_port), event, client_addr);
	this->_clients.push_back(client);
	std:: cout << TEXT_GREEN << "New connection from Client(" << client.getFD() << ") from: " << std::string(inet_ntoa(client_addr.sin_addr)) << ":" << ntohs(client_addr.sin_port) << TEXT_RESET << std::endl;

	return true;
}

bool Server::handleMessages(const int fd) {
	Client &client = this->getClientByFD(fd);
	if (client == *this->_clients.end()) {
		std::cerr << "Error: Client not found" << std::endl;
		return false;
	}

	std::string msg;
	char buffer[BUFFER_SIZE];
	int bytes_read = 0;

	std::cout << "[DEBUG] Reading fd: " << fd << std::endl; // TODO: remove
	bytes_read = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_read < 0) {
		std::cerr << "Error: Failed to read from socket err:" << bytes_read << std::endl;
		return false;
	}

	msg.append(buffer, bytes_read);

	// if bytes_read == BUFFER_SIZE - 1, there is more to read
	while (bytes_read == BUFFER_SIZE - 1) {
		bytes_read = recv(fd, buffer, BUFFER_SIZE - 1, 0);
		if (bytes_read < 0) {
			std::cerr << "Error: Failed to read from socket" << std::endl;
			return false;
		}
		msg.append(buffer, bytes_read);
	}

	// if bytes_read == 0 by recv, the client has disconnected
	if (msg.length() == 0) {
		this->disconnectClient(fd);
		return false;
	}

	client.recv_buffer.append(msg);

	std::cout << "[DEBUG] CURRENT BUFFER: "; // TODO: remove
	for (std::string::iterator it = client.recv_buffer.begin(); it != client.recv_buffer.end(); ++it) {
		if (*it == '\r')
			std::cout << "\\r";
		else if (*it == '\n')
			std::cout << "\\n";
		else
			std::cout << *it;
	}
	std::cout << std::endl; // TODO: remove

	while (client.recv_buffer.find("\r\n") != std::string::npos) {
		size_t position = client.recv_buffer.find("\r\n");

		std::string command = client.recv_buffer.substr(0, position);
		client.recv_buffer = client.recv_buffer.substr(position + 2); // remove command (with \r\n) from buffer

		client.setClientMessage(Message(command));

		std::cout << "[DEBUG] handling COMMAND: '" << command << "'" << std::endl; // TODO: remove

		// check the return value of commandsHandler since it's a Boolean return value
		commandsHandler(*this , client);
	}

	return true;
}

void Server::start() {
	initAllSignalHandlers();

	std::cout << "[DEBUG]" << std::endl << "Socket fd = " << this->_socket_fd << std::endl;

	global_status = e_RUN;
	while (global_status != e_STOP) {
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
				this->sendMsgToAll("The server is restarting...");
				global_status = e_RUN;

				break;
			}
			case e_STOP: {
				std::cout << TEXT_YELLOW << "Server stopping..." << TEXT_RESET << std::endl;
				this->disconnectAllClients();

				break;
			}
		}
		this->flush();
	}

	std::cout << TEXT_YELLOW << "Server stopped, exiting..." << TEXT_RESET << std::endl;
	close(this->_socket_fd);
}
