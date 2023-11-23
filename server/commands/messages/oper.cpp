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
		ERR_NEEDMOREPARAMS(client, message.msg);
		return;
	}
	if (message.args[0] != client.getNickname())
	{
		ERR_USERSDONTMATCH(client);
		return;
	}
	if (message.args[1] != "admin")
	{
		ERR_PASSWDMISMATCH(client);
		return ;
	}
	client.setOperatorMode(true);
    RPL_YOUREOPER(client);
	printMode(client);
	return;
}