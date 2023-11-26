#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

// https://modern.ircdocs.horse/#nick-message
void NICK(Server &server, Client &client) {
	Message message = client.getClientMessage();

	if (!client.isOnline())
	{
		return ;
	}
	if (message.args.size() != 1) {
		ERR_NEEDMOREPARAMS(client, message.cmd);
		ERR_NONICKNAMEGIVEN(client);
		client.setOnline(false);
		client.setIdentified(false);
		return;
	}

	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\/|_^";
	for (size_t i = 0; i < message.args[0].size(); i++) {
		if (allowedChars.find(message.args[0].at(i)) == std::string::npos) {
	 		ERR_ERRONEUSNICKNAME(client, message.args[0]);
			client.setOnline(false);
			client.setIdentified(false);
			return;
		}
	}

	// check if nickname is already in use
	for (size_t i = 0; i < server.clients.size(); i++) {
		if (server.clients[i].getNickname() == message.args[0]) {
			ERR_NICKNAMEINUSE(client, message.args[0]);
			client.setOnline(false);
			return;
		}
	}
	// TODO: change nick to all channels
	if (client.isRegistered() or client.isIdentified())
	{
		if (client.isRegistered())
		{

			client.setNickname(message.args[0]);
			std::string previousId = client.getID();
			client.setNickHistory(message.args[0]);
			client.setHasNick(true);

            client.setID(client.getNickname() + "!" + client.getUserName() + "@" + client.getHost());

			for (size_t i = 0; i < server.channels.size(); i++) {
            	Channel &channel = server.channels[i];
				if (channel.isclientConnected(previousId)) {
					bool isInvited = false;
					bool isOp = false;
					bool isBan = false;
					if (channel.isClientInvited(previousId))
					{
						channel.clientInvited.erase(previousId);
						isInvited = true;
					}
					if (channel.isClientOperatorChannel(previousId))
					{
						channel.clientOperators.erase(previousId);
						isOp = true;
					}
					if (channel.isClientBanned(previousId))
					{
						channel.clientBanned.erase(previousId);
						isBan = true;
					}
					channel.clientConnected.erase(previousId);
					channel.clientConnected.insert(client.getID());
					if (isInvited)
						channel.clientInvited.insert(client.getID());
					if (isBan)
						channel.clientBanned.insert(client.getID());
					if (isOp)
						channel.clientOperators.insert(client.getID());
            	}
        	}
		}
	}
	if (client.isIdentified())
	{
		sendNick(client);
	}
	return ;
}