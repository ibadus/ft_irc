#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"

#include <string>
#include <vector>

#define EPOLL_MAX_EVENTS 4096
class Server {
	public:
		Server(const unsigned int port, const std::string &password);
		~Server();

		std::string getPassword();
		int getPort();

		void start(const int fd);
		void flush();

	private:
		std::string _password;
		unsigned int _port;
		int _fd;

		std::vector<Client> _clients;
		std::vector<Channel> _channels;
};

#endif