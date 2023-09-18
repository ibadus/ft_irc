#include "commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#include <string>
#include <vector>
#include <iostream>

bool commandsHandler(std::string msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels, std::string password) {
	(void)msg;
	(void)client;
	(void)channels;
	(void)clients;
	(void)password;

	std::cout << "[" << msg.length() << "b] " << client.getNickname() << "(" << client.ID << ")" << ": " << msg << std::endl;

	return true;
}