#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"

#include <string>
#include <vector>
#include <sys/epoll.h>

#define EPOLL_MAX_EVENTS 4096

class Server {
	public:
		Server(const unsigned int port, const std::string &password);
		~Server();

		void start();
		void flush();

	private:
		std::string _password;
		unsigned int _port;
		int _socket_fd;
		int _epoll_fd;
		struct epoll_event _event;
		struct epoll_event _events[EPOLL_MAX_EVENTS];
		int _event_count;

		std::vector<Client> _clients;
		std::vector<Channel> _channels;

		bool initEpoll();
		bool handlePolling();
		bool handleNewConnection();
		bool handleMessages(const int fd);
};

#endif