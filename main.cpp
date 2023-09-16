#include "./include/server/parsing/parsing.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	unsigned int port;
	std::string password;

	if (!parseArgs(argc, argv, &port, &password)) {
		std::cerr << "Error: Invalid arguments. Use the following format :\n" << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}

	return 0;
}