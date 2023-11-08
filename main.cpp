#include "parsing.hpp"
#include "utils.hpp"
#include "Server.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	unsigned int port;
	std::string password;

	// validate arguments and set port and password
	if (!parseArgs(argc, argv, &port, &password)) {
		std::cerr << TEXT_RED << "Error: Invalid arguments. Use the following format :\n" << argv[0] << " <port> <password>" << TEXT_RESET << std::endl;
		return 1;
	}

	try {
		Server("IRC42", port, password).start();
	} catch (std::exception &e) {
		std::cerr << TEXT_RED << "Error: " << e.what() << TEXT_RESET << std::endl;
		return 1;
	}

	return 0;
}