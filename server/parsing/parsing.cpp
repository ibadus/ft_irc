#include "../../include/server/parsing/parsing.hpp"

bool parsePassword(std::string password) {
	if (password.length() < 1) {
		return false;
	}

	return true;
}

bool parsePort(std::string port) {
	if (port.length() < 1) {
		return false;
	}

	// TODO: check if port is a number

	// TODO: check if port is used

	return true;
}