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
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return(false);
	}
	if (!server.isChannelExisting(message.args[0]))
	{
        client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO: PUT THE RIGHT MESSAGE ERROR
		return(false);
	}
	if (!server.getChannel(message.args[0]).isclientConnected(client.getID()))
	{
        client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO: PUT THE RIGHT MESSAGE ERROR
		return(false);
	}
	if (!server.getChannel(message.args[0]).isClientOperatorChannel(client.getID())) 
	{
		client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO: PUT THE RIGHT MESSAGE ERROR
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