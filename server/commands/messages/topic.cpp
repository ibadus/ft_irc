#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void	TOPIC(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
    {
        return;
    }
	if (message.args.size() < 1)
	{
		return;
	}
	std::string channel = message.args[0];
	if(!server.isChannelExisting(channel))
    {
		return;
    }
	std::string currentTopic = server.getChannel(channel).getTopic();
	// if 0 parameter: send TOPIC name
	if (message.args.size() == 1)
	{	

		if (currentTopic == "")
            sendRplNoTopic(client, server.getChannel(channel));
		else
            sendRplTopic(client, server.getChannel(channel));
		return ;
	}
	else
	{
		if (server.getChannel(channel).getTopicLimitMode() and !server.getChannel(channel).isClientOperatorChannel(client.getID()))
		{
			return ;
		}
		std::string topicToSet = message.args[1];
		server.getChannel(channel).setTopic(message.args[1]);
		server.getChannel(channel).sendMessageToClients("332 " + client.getID() + " " + server.getChannel(channel).getChannelName() + " :" + topicToSet + "\r\n", "");
		return;
	}
}