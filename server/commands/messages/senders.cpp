#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

void sendRplWelcome(Server &server, Client &client)
{
	client.sendMsg("001 " + client.getNickname() +  " : Welcome to " + server.getServerName() + " Network, " + client.getID() + "\r\n" );
}


void RPL_UMODEIS(Client &client, std::string mode, std::string type)
{
	client.sendMsg(client.getID() + " 221 " + client.getNickname() + " " + mode + type + "\r\n");
}

void RPL_YOUREOPER(Client &client)
{
	client.sendMsg("381 " + client.getNickname() + " :You are now an IRC operator\r\n");
}

void RPL_WHOISUSER(Client &client)
{
	client.sendMsg(client.getNickname() + " " + client.getUserName() + " " + client.getHost() + " * :" + client.getRealName() + "\r\n");
}

void RPL_INVITING(Client &client, std::string invitenick, std::string channel)
{
	client.sendMsg("341 " + client.getID() + " " + invitenick + " " + channel + "\r\n");
}

void sendRplTopic(Client &client, Channel &channel)
{
	client.sendMsg("332 " + client.getID() + " " + channel.getChannelName() + " :" + channel.getTopic() + "\r\n");
}

void sendRplNoTopic(Client &client, Channel &channel)
{
	client.sendMsg("331 " +  client.getID() + " " + channel.getChannelName() + " :No topic is set\r\n");
}

void sendRplNamReply(Client &client, Channel &channel, std::string clientList)
{
	client.sendMsg("353 =" + client.getID() + " = " + channel.getChannelName() + " : " + clientList + "\r\n");
}

void sendRplEndOfNames(Client &client, Channel &channel)
{
	client.sendMsg("366 " + client.getID() +" " + channel.getChannelName() + " :End of NAMES list\r\n");
}

std::string sendJOIN(Client &client, std::string chanName)
{
 	return (":" + client.getID() + " JOIN " + chanName + "\r\n");
}


void sendPONG(Server &server, Client &client)
{
	client.sendMsg("PING " + server.getServerName() + "\r\n" );
}

void sendPING(Client &client, Message &message)
{
	client.sendMsg("PONG " + message.args[0] + "\r\n" );
}

void sendNick(Client &client)
{
	std::cout <<  "CLIENT PREVIOUS NICK :" << client.getPreviousNick() << std::endl;
	std::cout <<  "CLIENT NEW NICK :" << client.getNickname() << std::endl;

	client.sendMsg(":" + client.getPreviousNick() + " NICK " + client.getNickname() + "\r\n");
}

void sendQUIT(Client &client)
{
	client.sendMsg(client.getID() + " QUIT\r\n");
}

void sendQUITREASON(Client &client, std::string message)
{
	client.sendMsg(client.getID() + " QUIT " + message + "\r\n");
}

void sendQuitToAllExceptUser(Server &server, Client &client, std::string reason)
{
	std::string nickname = client.getNickname();
	for( std::vector<Client>::iterator it = server.getClientList().begin(); it != server.getClientList().end(); it++ )
	{
		if (it->getNickname() != nickname)
		{
			if (reason.size() != 0)
				sendQUITREASON(*it, reason);
			else 
				sendQUIT(*it);
		}
	}
}


void sendPART(Server &server, Client &client, std::string channel_name)
{
	server.getChannel(channel_name).sendMessageToClients(":" + client.getID() + " PART " + channel_name + "\r\n", "");
}

void sendPARTREASON(Server &server, Client &client, std::string channel_name, std::string reason)
{
	server.getChannel(channel_name).sendMessageToClients(":" + client.getID() + " PART " + channel_name + " :" + reason + "\r\n", "");
}

void RPL_NAMREPLY2(Client &client, std::string nickName, std::string channelName)
{
	client.sendMsg("353 =" + channelName + ":" + nickName + "\r\n");
}

void RPL_ENDOFNAMES2(Client &client, std::string channelName)
{
	client.sendMsg(client.getID() + "366 " + channelName + " :End of NAMES list\r\n");
}