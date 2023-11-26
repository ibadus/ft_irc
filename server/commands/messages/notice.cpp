#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"

#include <string>

void	NOTICE(Server &server, Client &client)
{
    Message message =  client.getClientMessage();
    if (!client.isOnline())
    {
        return;
    }
	if (message.args.size() < 2)
	{
		ERR_NEEDMOREPARAMS(client, message.cmd);
		return;
	}
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
	std::string msgToSend = ":" + client.getNickname() + " NOTICE " + nickNameClientReceiver + " " + msg + "\r\n";
	server.getClientByName(nickNameClientReceiver).sendMsg(msgToSend);
	return;
}