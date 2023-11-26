#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void	LIST(Server &server, Client  &client)
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
    std::vector<Channel> &channelList =  server.channels;
	for (std::vector<std::string>::iterator it = listOfChannelToShow.begin(); it != listOfChannelToShow.end(); it++)
	{
		channel_name = *it;
		toLowerStr(channel_name);
		for (std::vector<Channel>::iterator it_channel=channelList.begin(); it_channel != channelList.end(); it_channel++)
		{
			if (channel_name == "list" || channel_name == it_channel->getChannelName())
			{
                    client.sendMsg(client.getIDCMD() + "322 " + it_channel->getChannelName() + ":" + it_channel->getTopic() + "\r\n");
			}
		}
		client.sendMsg(client.getIDCMD() + "323 :End of List \r\n");
	}
    return;
}
