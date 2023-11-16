#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <string>

void	OPER(Client &client)
{
    Message message = client.getClientMessage();
	if (!client.isIdentified())
		return ;
	if (message.args.size() < 2)
	{
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (message.args[0] != client.getNickname())
	{
        client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (message.args[1] != "admin")
	{
		client.sendMsg("461 ERR_NEEDMOREPARAMS: wrong password");
		return ;
	}
	client.setOperatorMode(true);
    RPL_YOUREOPER(client);
	printMode(client);
	return;
}