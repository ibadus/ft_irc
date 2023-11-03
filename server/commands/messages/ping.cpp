#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"

#include <string>

// https://modern.ircdocs.horse/#ping-message
void PING(Client &client) {
	Message message = client.getClientMessage();
	if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}

	client.sendMsg("PONG " + message.args[0]);
}