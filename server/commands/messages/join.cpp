#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void JOIN(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
        return;
    if (message.args.size() != 1) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
    std::vector<std::string> listOfChannelToAdd = split(message.args[0], ",");
	std::string channel_name;

    	for (std::vector<std::string>::iterator it = listOfChannelToAdd.begin(); it != listOfChannelToAdd.end(); it++)
	{
		channel_name = *it;
		toLowerStr(channel_name);
		if (channel_name.size() <= 1 || !isChannelName(channel_name))
		{
			client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO: PUT THE RIGHT MESSAGE ERROR
			return;
		}
		else
		{
			if (!(server.isChannelExisting(channel_name)))
			{
				server.addChannel(channel_name);
			}
			if (server.getChannel(channel_name).getInviteMode())
			{
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO : PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else if (server.getChannel(channel_name).isClientBanned(client.getID()))
			{
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO :PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else
			{
				if (server.getChannel(channel_name).getClientOperator().size() == 0)
					server.getChannel(channel_name).addOperator(client.getID());
				server.getChannel(channel_name).addClient(client.getID());
			}
		}
	}
	return ;
}

