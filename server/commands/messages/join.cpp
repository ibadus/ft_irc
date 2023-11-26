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
    if (message.args.size() > 2) {
		ERR_NEEDMOREPARAMS(client, message.cmd);
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
			ERR_NOSUCHCHANNEL(client, channel_name);
			return;
		}
		else
		{
			if (!(server.isChannelExisting(channel_name)))
			{
				server.addChannel(channel_name);
			}
			if (server.getChannel(channel_name).getInviteMode() && !server.getChannel(channel_name).isClientInvited(client.getID()))
			{
				ERR_INVITEONLYCHAN(client, channel_name);
				return;
			}
			if (server.getChannel(channel_name).getPasswMode() && ( (int)message.args.size() != 2 || server.getChannel(channel_name).getChannelPassw() != message.args[1]))
			{
				ERR_BADCHANNELKEY(client,channel_name);
				return;
			}
			if (server.getChannel(channel_name).getSizeLimitMode() && (static_cast<int>(server.getChannel(channel_name).getSizeLimit()) <= static_cast<int>(server.getChannel(channel_name).clientConnected.size())))
			{
				ERR_CHANNELISFULL(client, channel_name); // TODO : PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else if (server.getChannel(channel_name).isClientBanned(client.getID()))
			{
				ERR_BANNEDFROMCHAN(client, channel_name); // TODO :PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else
			{
				if (server.getChannel(channel_name).clientOperators.size() == 0)
					server.getChannel(channel_name).addOperator(client.getID());
				server.getChannel(channel_name).addClient(client.getID());
			}
		}
	}
	return ;
}
