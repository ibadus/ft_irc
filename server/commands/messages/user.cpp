#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include <iostream>

void	USER(Server &server, Client &client)
{
    Message message = client.getClientMessage();
	if (client.isRegistered() and client.getHasNick())
	{
		if (message.args.size() != 0)
		{
			if (message.args.size() > 4)
			{
				client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
				return;
			}
            client.setUserName(message.args[1]);
            client.setRealName(message.args[3]);
            client.setID(client.getNickname() + "!" + client.getUserName() + "@" + client.getHost());
			sendRplWelcome(server, client);
			client.setIdentified(true);
			return;
		}
		else if (client.isIdentified() == true)
		{
			client.sendMsg("462 :You may not reregister\r\n");
			return;
		}
	}
	return;
}
