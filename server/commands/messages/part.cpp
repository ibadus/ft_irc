#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void	PART(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
        return;
    if (message.args.size() != 1) {
		ERR_NEEDMOREPARAMS(client, message.cmd);
		return;
	}
	std::vector<std::string> listOfChannelToRemove = split(message.args[0], ",");
	std::string channel_name;
	for (std::vector<std::string>::iterator it = listOfChannelToRemove.begin(); it != listOfChannelToRemove.end(); it++)
	{
		channel_name = *it;
		toLowerStr(channel_name);
		if (!server.isChannelExisting(channel_name))
		{
			ERR_NOSUCHCHANNEL(client, channel_name);
			return ;
		}
		else if (!server.getChannel(channel_name).isclientConnected(client.getID()))
		{
            ERR_NOTONCHANNEL(client,channel_name);
			return ;
		}
		else
		{
			if (message.args.size() > 1)
			{
				std::string leavingReason = message.args[1];
                sendPARTREASON(server, client, channel_name, leavingReason);
            }
			else
			{
                sendPART(server, client, channel_name);
			}
			server.getChannel(channel_name).removeConnected(client.getID());
		}
	}
	return ;
}
