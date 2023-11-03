#include "Message.hpp"
#include "Client.hpp"
#include "utils.hpp"

#include <string>
#include <exception>
#include <vector>
#include <iostream>


Message::Message(){}

Message::Message(std::string line): msg(line){
	std::string::size_type pos = msg.find(' ');
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid command");

	cmd = line.substr(0, pos);
	for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it)
		*it = toupper(*it);
	line.erase(0, pos + 1);
	while ((pos = line.find(' ')) != std::string::npos) {
		args.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	args.push_back(line);

	std::cout << TEXT_UNDERLINE << cmd << " | " << args.size() << " args:" << TEXT_RESET << std::endl;
	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
		std::cout << "\t" << *it << std::endl;
}

Message::~Message() {}