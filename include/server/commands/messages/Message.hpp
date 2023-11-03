#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>

class Message {
	public:
	    Message();
		Message(std::string line);
		~Message();

		std::string msg;
		std::string cmd;
		std::vector<std::string> args;
	private:

};

#endif