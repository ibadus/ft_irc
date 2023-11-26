#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"

#include <string>

void	PRIVMSG(Server &server, Client &client)
{
    Message message =  client.getClientMessage();
    if (!client.isOnline())
    {
        return;
    }
	if (message.args.size() < 1)
	{
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (isChannelName(message.args[0]))
	{
		std::string channelName = message.args[0];
        std::string msg;
        for (int i = 1; i < (int)message.args.size(); i++)
        {
            msg += message.args[i];
            if (i != (int)message.args.size() - 1)
                msg += " ";
        }
		Channel& channel = server.getChannel(channelName);
		if (!server.isChannelExisting(channelName))
		{
			ERR_NOSUCHCHANNEL(client,channelName);
			return;
		}
		if (channel.isClientBanned(client.getID()))
		{
		    ERR_BANNEDFROMCHAN(client, channelName);
			return;
		}
		if (!channel.isclientConnected(client.getID()))
		{
			ERR_NOTREGISTERED(client);
			return;
		}
		std::string msgToSend = ":" + client.getNickname() + " PRIVMSG " + channelName + " " + msg + "\r\n";
		channel.sendMessageToClients(msgToSend, client.getNickname());
		return;
	}
	else
	{
		std::string nickNameClientReceiver = message.args[0];
		if (!server.isClientExisting(nickNameClientReceiver))
		{
			ERR_NOSUCHNICK(client, nickNameClientReceiver);
			return;
		}
        std::string msg;
        for (int i = 1; i < (int)message.args.size(); i++)
        {
            msg += message.args[i];
            if (i != (int)message.args.size() - 1)
                msg += " ";
        }
		std::string msgToSend = ":" + client.getNickname() + " PRIVMSG " + nickNameClientReceiver + " :" + msg + "\r\n";
		server.getClientByName(nickNameClientReceiver).sendMsg(msgToSend);
		return;
	}
	return;
}
