#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

// https://modern.ircdocs.horse/#nick-message
void NICK(Server &server, Client &client) {
	std::vector<Client> clientList = server.getClientList();
	Message message = client.getClientMessage();

	if (message.args.size() != 1) {
		ERR_NEEDMOREPARAMS(client, message.cmd);
		ERR_NONICKNAMEGIVEN(client);
		client.setOnline(false);
		client.setIdentified(false);
		return;
	}

	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\/|_^";
	for (size_t i = 0; i < message.args[0].size(); i++) {
		if (allowedChars.find(message.args[0].at(i)) == std::string::npos) {
	 		ERR_ERRONEUSNICKNAME(client, message.args[0]);
			client.setOnline(false);
			client.setIdentified(false);
			return;
		}
	}

	// check if nickname is already in use
	for (size_t i = 0; i < clientList.size(); i++) {
		if (clientList[i].getNickname() == message.args[0]) {
			ERR_NICKNAMEINUSE(client, message.args[0]);
			client.setOnline(false);
			return;
		}
	}
	// TODO: change nick to all channels
	if (client.isRegistered() or client.isIdentified())
	{
		if (client.isRegistered())
		{
			client.setNickname(message.args[0]);
			client.setNickHistory(message.args[0]);
			client.setHasNick(true);
		}
		if (client.isIdentified())
		{
			sendNick(client);
		}
		return ;
	}
	// std::cout << "MESSAGE ARGS[0]: " << message.args[0] << std::endl;
	// std::cout << "CLIENT NICKNAME:  " << client.getNickname() << std::endl;
}