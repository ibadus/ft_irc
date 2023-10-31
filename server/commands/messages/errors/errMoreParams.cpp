#include "utils.hpp"

#include <string>
#include <iostream>

std::string errMoreParams() {
	return std::string(TEXT_RED + "461 ERR_NEEDMOREPARAMS: Invalid parameters number" + TEXT_RESET + std::endl);
}