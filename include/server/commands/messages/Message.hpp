#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Client.hpp"

#include <string>
#include <vector>

class Message {
	public:
		Message(std::string line, Client &client);
		~Message();

		std::string msg;
		std::string cmd;
		std::vector<std::string> args;
		Client &client;
	private:

};

#endif