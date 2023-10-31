#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"

#include <string>

// https://modern.ircdocs.horse/#nick-message
void NICK(Message msg, std::vector<Client> &clients) {
	if (msg.args.size() != 1) {
		msg.client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}

	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\/|_^";
	for (size_t i = 0; i < msg.args[0].size(); i++) {
		if (allowedChars.find(msg.args[0].at(i)) == std::string::npos) {
			msg.client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname.");
			return;
		}
	}

	// check if nickname is already in use
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i].getNickname() == msg.args[0]) {
			msg.client.sendMsg("433 ERR_NICKNAMEINUSE:Nickname is already in use.");
			return;
		}
	}

	// TODO: change nick to all channels
	msg.client.setNickname(msg.args[0]);
}