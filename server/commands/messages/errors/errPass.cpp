#include "utils.hpp"

#include <string>
#include <iostream>

std::string errMoreParams() {
	return std::string(TEXT_RED + "464 ERR_PASSWDMISMATCH:Invalid password" + TEXT_RESET + std::endl);
}