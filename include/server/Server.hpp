#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server {
	public:
		Server();
		~Server();

		std::string getPassword();
		int getPort();

		void start(int port, std::string password);

	private:
		std::string password;
		int port;
};

#endif