#pragma once

#include <string>
#include <vector>
#include <sys/epoll.h>
#include "Client.hpp"
#include "Channel.hpp"
// Defines the maximum size of the batch of IO events to process on
// each loop iteration. A larger number will increase throughput but
// decrease concurrency.
#define EPOLL_MAX_EVENTS 32

// Defines the maximum size of the buffer used to receive incoming messages.
#define BUFFER_SIZE 1024

#define MAX_CLIENTS 25

class Client;

class Server {
		public:
		Server(const std::string &name, const unsigned int port, const std::string &password);
		~Server();
		std::string getServerPassword() const { return this->_password; }
		std::vector<Client> getClientList() const { return this->_clients;}
		std::vector<Channel> getChannelList() const { return this->_channels; }
		Channel &getChannel(std::string chanName);
		void addChannel(std::string chanName);
		bool	isChannelExisting(std::string name);
		bool 	isClientExistingID(std::string ID);
		bool	isClientExisting(std::string Nickname);
		std::vector<Client>::iterator getClientByFD(const int fd);
		Client &getClient(std::string ID);
		Client &getClientByName(std::string nickName);
		std::string getServerName() {return this->_name;}
		void start();
		void flush();

	private:
		std::string _name;
		std::string _password;
		unsigned int _port;
		int _socket_fd;
		int _epoll_fd;
		int _event_count;

		std::vector<Client> _clients;
		std::vector<Channel> _channels;

		std::vector<struct epoll_event> _events;
		struct epoll_event _event;

		void disconnectClient(const int fd);
		void disconnectAllClients();
		void sendMsgToAll(std::string msg);
		bool initEpoll();
		bool handlePolling();
		bool handleNewConnection(struct epoll_event &event);
		bool handleMessages(const int fd);
};