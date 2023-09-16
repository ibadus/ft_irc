#include "signals.hpp"
#include "status.hpp"
#include "utils.hpp"

#include <iostream>

void sigIntHandler(int s) {
	(void)s;
	std::cout << TEXT_YELLOW << "Interrupt signal received." << TEXT_RESET << std::endl;
	global_status = e_STOPPED;
}