#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h> // sockaddr_in
#include <sys/epoll.h> // epoll_event

class Client
{
	public:
		size_t ID;

		std::string recv_buffer;

		Client(int fd, std::string host, int port, struct epoll_event event, struct sockaddr_in addrinfo);
		~Client();

		bool operator==(const Client &other) const {
			return this->_fd == other.getFD() && this->_host == other.getHost() && this->_port == other.getPort();
		}

		int getFD() const { return this->_fd; }
		std::string getHost() const { return this->_host; }
		int getPort() const { return this->_port; }
		struct epoll_event getEvent() const { return this->_conn_event; }
		struct sockaddr_in getAddrinfo() const { return this->_addrinfo; }
		std::string getNickname() const { return this->_nickname; }
		void setNickname(std::string nickname) { this->_nickname = nickname; }

		void sendMsg(std::string msg);
		void disconnect();

		bool isRegistered() const { return this->_registered; }
		void setRegistered(bool registered) { this->_registered = registered; }

		bool isIdentified() const { return this->_identified; }
		void setIdentified(bool identified) { this->_identified = identified; }
	private:
		static size_t g_ID; // auto increment

		int _fd;
		std::string _host;
		int _port;

		struct epoll_event _conn_event;
		struct sockaddr_in 	_addrinfo;

		std::string _nickname;

		bool _registered;
		bool _identified;

};

#endif