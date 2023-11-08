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

// void sendRplWhoIsUser(Server &server, Client &client)
// {
// 	# define RPL_WHOISUSER(nick, user, host, realname) ( nick + " " + user + " " + host +" * :" + realname + "\r\n")
// }

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

// void sendQUIT()
// {
// 	":" + old_nick + " NICK " + nick + "\r\n"
// }