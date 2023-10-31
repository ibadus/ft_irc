#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"

#include <string>

// https://modern.ircdocs.horse/#ping-message
void PING(Message &msg) {
	if (msg.args.size() != 1) {
		msg.client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}

	msg.client.sendMsg("PONG " + msg.args[0]);
}