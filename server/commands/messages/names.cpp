#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void	NAMES(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
    {
        return;
    }
	std::vector<std::string> listOfChannelToShow;
	if (message.args.size() != 1)
		listOfChannelToShow = split(message.args[1], ",");
	else
		listOfChannelToShow = split(message.args[0], ",");
	
	std::string channel_name;
    std::vector<Channel> channelList =  server.getChannelList();
	for (std::vector<std::string>::iterator it = listOfChannelToShow.begin(); it != listOfChannelToShow.end(); it++)
	{
		channel_name = *it;
		toLowerStr(channel_name);
		for (std::vector<Channel>::iterator it_channel=channelList.begin(); it_channel != channelList.end(); it_channel++)
		{
			if (channel_name == "names" || channel_name == it_channel->getChannelName())
			{
				for (std::set<std::string>::iterator it_client=it_channel->clientConnected.begin(); it_client != it_channel->clientConnected.end(); it_client++)
				{
					RPL_NAMREPLY2(client, server.getClient(*it_client).getNickname(), it_channel->getChannelName());
				}
                RPL_ENDOFNAMES2(client, it_channel->getChannelName());
			}
		}
	}
	return ;
}