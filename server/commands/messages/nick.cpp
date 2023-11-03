#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"

#include <string>

// https://modern.ircdocs.horse/#nick-message
void NICK(Server &server, Client &client) {
	std::vector<Client> clientList = server.getClientList();
	Message message = client.getClientMessage();

	if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}

	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\/|_^";
	for (size_t i = 0; i < message.args[0].size(); i++) {
		if (allowedChars.find(message.args[0].at(i)) == std::string::npos) {
			client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname.");
			return;
		}
	}

	// check if nickname is already in use
	for (size_t i = 0; i < clientList.size(); i++) {
		if (clientList[i].getNickname() == message.args[0]) {
			client.sendMsg("433 ERR_NICKNAMEINUSE:Nickname is already in use.");
			return;
		}
	}

	// TODO: change nick to all channels
	//msg.client.setNickname(msg.args[0]);
}