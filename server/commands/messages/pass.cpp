#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

// https://modern.ircdocs.horse/#pass-message
void PASS(Server &server, Client &client) {

	Message message = client.getClientMessage();
	if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		client.setOnline(false);
		return;
	}

	if (client.isRegistered()) {
		client.sendMsg("462 ERR_ALREADYREGISTRED:You are already registered.");
		client.setOnline(false);
		return;
	}
	if (message.args[0] == server.getServerPassword()) {
		client.setRegistered(true);
		return;
	} else {
		client.sendMsg("464 ERR_PASSWDMISMATCH:Invalid password.");
		client.sendMsg(TEXT_RED + std::string("Password incorrect.") + TEXT_RESET);
		client.setOnline(false);
		client.disconnect();
	}
}