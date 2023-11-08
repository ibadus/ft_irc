#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"

#include <string>

void PONG(Client &client) {
	Message message = client.getClientMessage();
	if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (!client.isIdentified())
		return;

	sendPING(client, message);
}