#include "utils.hpp"

#include <string>
#include <sstream>

int toInt(std::string s) {
	int n;
	std::stringstream ss(s);

	ss >> n;
	return n;
}