#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server {
	public:
		Server();
		~Server();

		std::string getPassword();
		int getPort();

		void start(const int port, const std::string &password);

	private:
		std::string password;
		int port;
};

#endif