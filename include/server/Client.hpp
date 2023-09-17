#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event

class Client
{
	public:
		static size_t ID; // auto increment

		Client(int fd, std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo);
		~Client();

		int getFD() const { return this->_fd; }
		std::string getHost() const { return this->_host; }
		int getPort() const { return this->_port; }
		struct epoll_event getEvent() const { return this->_conn_event; }
		struct sockaddr_in getAddrinfo() const { return this->_addrinfo; }
		std::string getNickname() const { return this->_nickname; }

		void sendMsg(std::string msg);
		void disconnect();
	private:
		int _fd;
		std::string _host;
		int _port;

		struct epoll_event _conn_event;
		struct sockaddr_in 	_addrinfo;

		std::string _nickname;
};

#endif