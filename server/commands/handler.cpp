#include "commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "messages.hpp"

#include <string>
#include <vector>
#include <iostream>

bool commandsHandler(Server &server, Client &client) {

	Message message = client.getClientMessage();

	std::cout << TEXT_GREEN << "[" << message.msg.length() << "b] " << client.getFD() << "(" << client.ID << ")" << "cmd: " << message.cmd << TEXT_RESET << std::endl;

	if (message.cmd == "PASS") {
		PASS(server, client);
	} else if (message.cmd == "PING") { 
		PONG(client);
	}
	else if (message.cmd == "PONG") {
		PING(server, client);
	}
	else if (message.cmd == "NICK") { // Changes your nickname on the active server
		NICK(server, client);
	}
	else if (message.cmd == "USER") 
	{
		USER(server, client);
	} else if (message.cmd == "MODE")
	{
		MODE(server, client);
	}

	if (!client.isRegistered())
		return true;
	// past this point, the client is registered
	if (!client.isIdentified())
		return true;
	// past this point, the user has registered and identifie
	if (message.cmd == "JOIN")
		JOIN(server, client);
	else if (message.cmd == "WHOIS")
		WHOIS(server, client);
	else if (message.cmd == "OPER")
		OPER(client);
	else if (message.cmd == "INVITE")
		INVITE(server, client);
	else if (message.cmd == "PART")
		PART(server, client);
	else if (message.cmd == "KICK")
		KICK(server, client);
	else if (message.cmd == "PRIVMSG")
		PRIVMSG(server, client);
	else if (message.cmd == "NOTICE")
		NOTICE(server, client);
	else if (message.cmd == "TOPIC")
		TOPIC(server, client);
	else if (message.cmd == "LIST")
		LIST(server, client);
	else if (message.cmd == "QUIT")
	{
		QUIT(server, client);
		return (false);
	}

	return true;
}