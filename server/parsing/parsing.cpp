#include "parsing.hpp"
#include "utils.hpp"

#include <string>

static std::string parsePassword(std::string password) {
	if (password.length() < 1) {
		return "";
	}

	return password;
}

static int parsePort(std::string port) {
	if (port.length() < 1) {
		return -1;
	}

	for (size_t i = 0; i < port.length(); i++) {
		if (std::isdigit(port[i]) == false)
			return -1;
		if (i > 5)
			return -1;
	}

	int iport = toInt(port);
	if (iport < 0 || iport > 65535)
		return -1;

	return iport;
}

bool parseArgs(int argc, char** argv, unsigned int *port, std::string *password) {
	if (argc != 3) {
		return false;
	}

	int p = parsePort(argv[1]);
	std::string pass = parsePassword(argv[2]);

	if (p < 0 || pass.length() < 1) {
		return false;
	}

	*port = p;
	*password = pass;

	return true;
}