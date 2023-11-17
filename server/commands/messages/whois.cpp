#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <string>

void	printMode(Client &client)
{
	if (client.isInvisibleMode())
        RPL_UMODEIS(client, "+", "i");
	if (client.isOperatorMode())
		RPL_UMODEIS(client, "+", "o");
}

void	WHOIS(Server &server, Client &client)
{
	(void)server;
    Message message = client.getClientMessage();
	if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (!client.isIdentified())
		return ;
    RPL_WHOISUSER(client);
	printMode(client);
}