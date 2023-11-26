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
	client.sendMsg(client.getIDCMD() + " 221 " + client.getNickname() + " " + mode + type + "\r\n");
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
	client.sendMsg(":" + client.getPreviousNick() + " NICK " + client.getNickname() + "\r\n");
}

void sendQUIT(Client &receiver, Client &leaver)
{
	receiver.sendMsg(leaver.getID() + " QUIT\r\n");
}

void sendQUITREASON(Client &receiver, Client &leaver ,std::string message)
{
	receiver.sendMsg(leaver.getID() + " QUIT " + message + "\r\n");
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
	client.sendMsg(client.getIDCMD() + "366 " + channelName + " :End of NAMES list\r\n");
}

void RPL_CHANNELMODEIS(Client &client, std::string channelName, std::string mode)
{
	client.sendMsg( client.getID() + " 324 " + client.getNickname() + " " + channelName + " " + mode + "\r\n");	
}

void RPL_CHANNELMODEISTOALL(Client &client, std::string channelName, std::string mode)
{
	client.sendMsg( client.getID() + " 324 " + client.getNickname() + " " + channelName + " " + mode + "\r\n");
}

/// ERROR RPL

void ERR_NOSUCHCHANNEL(Client &client, std::string channel_name)
{
	 client.sendMsg(":" + client.getHost() + " 403 " + client.getNickname() + " " + channel_name + " :No such channel\r\n");
}

void ERR_NOSUCHNICK(Client &client, std::string receiver)
{
	client.sendMsg(":" + client.getHost() + " 401 " + client.getNickname() + " " + receiver + " :No such nick/channel\r\n");
}

void ERR_NEEDMOREPARAMS(Client &client, std::string command)
{
	client.sendMsg(":" + client.getHost() + " 461 " + client.getNickname() + " " + command + " : Not enough parameters\r\n");
}

void ERR_CHANOPRIVSNEEDED(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 482 " + client.getNickname() + " " + channel_name + " :You're not channel operator\r\n");
}

void ERR_USERONCHANNEL(Client &client, std::string channel_name, std::string nickName )
{
	client.sendMsg(":" + client.getHost() + " 443 " + client.getNickname() + " " + nickName + " " + channel_name + " :is already on channel\r\n");
}

void ERR_NOTONCHANNEL(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 442 " + client.getNickname() + " " + channel_name + " :You're not on that channel\r\n");
}

void ERR_NOTREGISTERED(Client &client)
{
	 client.sendMsg(":" + client.getHost() + " 451 " + " :You have not registered\r\n");
}

void ERR_INVITEONLYCHAN(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 473 " + client.getNickname() + " " + channel_name + " :Cannot join channel (+i)\r\n");
}

void ERR_BADCHANNELKEY(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 475 " + client.getNickname() + " " + channel_name + " :Cannot join channel (+k)\r\n");
}

void ERR_CHANNELISFULL(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 471 " + client.getNickname() + " " + channel_name + " :Cannot join channel (+l)\r\n");
}

void ERR_BANNEDFROMCHAN(Client &client, std::string channel_name)
{
	client.sendMsg(":" + client.getHost() + " 471 " + client.getNickname() + " " + channel_name + " :Cannot join channel (+b)\r\n");
}

void ERR_USERNOTINCHANNEL(Client &client, std::string nickName, std::string channel_name)
{
	 client.sendMsg(":" + client.getHost() + " 451 " + nickName + " " + channel_name + " :They aren't on that channel\r\n");
}

void ERR_USERSDONTMATCH(Client &client)
{
	 client.sendMsg(":" + client.getHost() + " 502 " + " :Cant change mode for other users\r\n");
}

void ERR_NONICKNAMEGIVEN(Client &client)
{
	 client.sendMsg(":" + client.getHost() + " 431 " + " ::No nickname given\r\n");
}

void ERR_NICKNAMEINUSE(Client &client, std::string nickName)
{
	client.sendMsg(":" + client.getHost() +  " 433 " + nickName + " :Nickname is already in use\r\n");
}

void ERR_ERRONEUSNICKNAME(Client &client, std::string nickName)
{
	client.sendMsg(":" + client.getHost() +  " 432 " + nickName + " :Erroneus nickname\r\n");
}

void ERR_PASSWDMISMATCH(Client &client)
{
	client.sendMsg(":" + client.getHost() +  " 464 " + ":Password incorrect\r\n");
}