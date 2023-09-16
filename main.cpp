#include "parsing.hpp"
#include "socket.hpp"
#include "utils.hpp"
#include "signals.hpp"

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
	std::cout << TEXT_GREEN << argv[0] << " listening on port " << port << TEXT_RESET << std::endl;
	
	signal(SIGINT, sigIntHandler); // allows to ctrl+c the server once it's started
	
	// TODO: handle the start and all the commands
	return 0;
}