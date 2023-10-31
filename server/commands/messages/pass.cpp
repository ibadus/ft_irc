#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"

#include <string>

// https://modern.ircdocs.horse/#pass-message
void PASS(Message &msg, std::string password) {
	if (msg.args.size() != 1) {
		msg.client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}

	if (msg.client.isRegistered()) {
		msg.client.sendMsg("462 ERR_ALREADYREGISTRED:You are already registered.");
		return;
	}

	if (msg.args[0] == password) {
		msg.client.setRegistered(true);
		return;
	} else {
		msg.client.sendMsg("464 ERR_PASSWDMISMATCH:Invalid password.");
		msg.client.sendMsg(TEXT_RED + std::string("Password incorrect.") + TEXT_RESET);
		msg.client.disconnect();
	}
}