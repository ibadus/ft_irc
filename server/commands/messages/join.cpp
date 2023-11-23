#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>

#include <string>

void JOIN(Server &server, Client &client)
{
    Message message = client.getClientMessage();
    if (!client.isOnline())
        return;
    if (message.args.size() > 2) {
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
    std::vector<std::string> listOfChannelToAdd = split(message.args[0], ",");
	std::string channel_name;

    for (std::vector<std::string>::iterator it = listOfChannelToAdd.begin(); it != listOfChannelToAdd.end(); it++)
	{
		channel_name = *it;
		toLowerStr(channel_name);
		if (channel_name.size() <= 1 || !isChannelName(channel_name))
		{
			client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO: PUT THE RIGHT MESSAGE ERROR
			return;
		}
		else
		{
			if (!(server.isChannelExisting(channel_name)))
			{
				std::cout << "CHANNEL EXISTING BUT NO WE CREATING ON" << std::endl;
				server.addChannel(channel_name);
			}
			if (server.getChannel(channel_name).getInviteMode() && !server.getChannel(channel_name).isClientInvited(client.getID()))
			{
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO : PUT THE RIGHT MESSAGE ERROR
				return;
			}
			std::cout << "Channel mode key :" << server.getChannel(channel_name).getPasswMode() << std::endl;
			std::cout << "Channel key :" << server.getChannel(channel_name).getChannelPassw() << std::endl;
			std::cout << "CHANNEL NAME = :" << server.getChannel(channel_name).getChannelName() << std::endl;
			if (server.getChannel(channel_name).getPasswMode() && ( (int)message.args.size() != 2 || server.getChannel(channel_name).getChannelPassw() != message.args[1]))
			{
				std::cout << "MESSAGE SIZE JOIN :" << message.args.size() << std::endl;
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO : PUT THE RIGHT MESSAGE ERROR
				return;
			}			
			if (server.getChannel(channel_name).getSizeLimitMode() && (static_cast<int>(server.getChannel(channel_name).getSizeLimit()) >= static_cast<int>(server.getChannel(channel_name).getClientConnectList().size())))
			{
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO : PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else if (server.getChannel(channel_name).isClientBanned(client.getID()))
			{
				client.sendMsg("432 ERR_ERRONEUSNICKNAME:You cannot use this nickname."); // TODO :PUT THE RIGHT MESSAGE ERROR
				return;
			}
			else
			{
				if (server.getChannel(channel_name).getClientOperator().size() == 0)
					server.getChannel(channel_name).addOperator(client.getID());
				server.getChannel(channel_name).addClient(client.getID());
			}
		}
	}
	return ;
}

