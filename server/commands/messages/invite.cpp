#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <string>


bool	isValidParsingINVITE(Server &server, Client &client)
{
    Message message = client.getClientMessage();
	if (message.args.size() < 2)
	{
		ERR_NEEDMOREPARAMS(client, message.cmd);
		return (false);
	}
  	if (!server.isClientExisting(message.args[0]))
  	{
		ERR_NOSUCHNICK(client, message.args[0]);
		return (false);
  	}
  	if (!server.isChannelExisting(message.args[1]))
	{
		ERR_NOSUCHCHANNEL(client, message.args[1]);
		return (false);
	}
	if (!server.getChannel(message.args[1]).isclientConnected(client.getID()))
	{
		ERR_NOTONCHANNEL(client, message.args[1]);
		return (false);
	}
  	if (server.getChannel(message.args[1]).isclientConnected(server.getClientByName(message.args[0]).getID()))
  	{
		ERR_USERONCHANNEL(client, message.args[1], message.args[0]);
		return (false);  
  	}
  	if (server.getChannel(message.args[1]).getInviteMode() == true)
  	{
		if (!server.getChannel(message.args[1]).isClientOperatorChannel(client.getID()))
		{
	  		ERR_CHANOPRIVSNEEDED(client, message.args[1]);
	  		return(false);
		} 
  	}
  	return (true);
}

void	INVITE(Server &server, Client &client)
{
    Message message = client.getClientMessage();
	if (!client.isIdentified())
		return ;
	if (!isValidParsingINVITE(server, client))
		return;
	server.getChannel(message.args[1]).addClient(server.getClientByName(message.args[0]).getID());
	server.getChannel(message.args[1]).addInvited(server.getClientByName(message.args[0]).getID());
    RPL_INVITING(client, message.args[0], message.args[1]);
	server.getClientByName(message.args[0]).sendMsg("341 " + client.getID() + " " + message.args[0] + " " + message.args[1] + "\r\n");
	return ;
}