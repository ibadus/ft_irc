#include "parsing.hpp"
#include "socket.hpp"
#include "utils.hpp"
#include "signals.hpp"
#include "Server.hpp"

#include <iostream>
#include <string>
#include <signal.h>

int main(int argc, char** argv) {
	unsigned int port;
	std::string password;

	// validate arguments and set port and password
	if (!parseArgs(argc, argv, &port, &password)) {
		std::cerr << TEXT_RED << "Error: Invalid arguments. Use the following format :\n" << argv[0] << " <port> <password>" << TEXT_RESET << std::endl;
		return 1;
	}

	// start server
	int fd = initSocket(port);
	if (fd < 0) {
		std::cerr << TEXT_RED << "Error: Could not start server." << TEXT_RESET << std::endl;
		return 2;
	}
	port = getPort(fd);

	signal(SIGINT, sigIntHandler); // allows to ctrl+c the server once it's started

	try {
		Server(port, password).start(fd);
	} catch (std::exception &e) {
		std::cerr << TEXT_RED << "Unexpected Error: " << e.what() << TEXT_RESET << std::endl;
		return 1;
	}

	return 0;
}