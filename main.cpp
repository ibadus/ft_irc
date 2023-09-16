#include <iostream>


int main(int argc, char** argv) {
	std::cout << "[DEBUG] " << argc << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << "\t[" << i << "] - " << argv[i] << std::endl;
	}

	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}

	return 0;
}