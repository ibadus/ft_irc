#include "signals.hpp"
#include "status.hpp"
#include "utils.hpp"

#include <iostream>

void sigIntHandler(int s) {
	(void)s;
	std::cout << "\r"; // Clear the ^C from the terminal (reset terminal cursor position to the beginning of the line)
	std::cout << TEXT_YELLOW << "Interrupt signal received." << TEXT_RESET << std::endl;
	global_status = e_STOP;
}