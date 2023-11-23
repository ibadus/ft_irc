#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>


bool	isValidParsingKICK(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (message.args.size() < 2) {
		ERR_NEEDMOREPARAMS(client, message.cmd);
		return(false);
	}
	if (!server.isChannelExisting(message.args[0]))
	{
        ERR_NOSUCHCHANNEL(client, message.args[0]);
		return(false);
	}
	if (!server.getChannel(message.args[0]).isclientConnected(server.getClientByName(message.args[1]).getID()))
	{
        ERR_USERNOTINCHANNEL(client, message.args[1], message.args[0]);
		return(false);
	}
		if (!server.getChannel(message.args[0]).isclientConnected(client.getID()))
	{
		return(false);
	}
	if (!server.getChannel(message.args[0]).isClientOperatorChannel(client.getID())) 
	{
		ERR_CHANOPRIVSNEEDED(client, message.args[0]); 
		return (false);
	}
	return (true);
}

void   KICK(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
    {
        return;
    }
	if (!isValidParsingKICK(server, client))
		return;
	Client client_remove = server.getClientByName(message.args[1]);
    sendPART(server, client_remove, message.args[0]);
    server.getChannel(message.args[0]).removeConnected(server.getClientByName(message.args[1]).getID());
	return;
}