#include "../../include/server/parsing/parsing.hpp"

#include <string>

bool parsePassword(std::string password) {
	if (password.length() < 1) {
		return false;
	}

	return true;
}

int parsePort(std::string port) {
	if (port.length() < 1) {
		return -1;
	}

	for (int i = 0; i < port.length(); i++) {
		if (std::isdigit(port[i]) == false)
			return -1;
		if (i > 5)
			return -1;
	}

	return std::atoi(port.c_str());
}