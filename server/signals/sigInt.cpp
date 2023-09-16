#include "signals.hpp"

#include <iostream>

void sigIntHandler(int s) {
	(void)s;
	std::cout << "Interrupt signal received. Exiting..." << std::endl;
}