#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>
#include <string>

#define USER_MODE 0
#define CHANNEL_MODE 1

int		parseModes(Server &server, Client &client, std::string modes, int modeType, std::string arg, std::string chan )
{
	size_t j = 0;
	for (j = 0; j < modes.size(); j++)
	{
		if (modes[j] == '+' or modes[j] == '-')
		{
			if (modeType == USER_MODE)
				updateUserModes(client, modes[j], modes[j + 1]);
			else
			{
				switch(modes[j + 1])
				{
					case 'i':
						handleInviteOnlyMode(server, client, modes[j], modes[j + 1], chan);
						break;
					case 'o':
						handleOperatorChannelMode(server, client, modes[j], modes[j + 1], arg, chan);
						break;
					case 'k':
						handlePasswChannelMode(server, client, modes[j], modes[j + 1], arg, chan);
						break;
					case 't':
						handleTopicRestrictChannelMode(server, client, modes[j], modes[j + 1], chan);
					case 'l':
						handleSizeChannelMode(server, client, modes[j], modes[j + 1], args,  chan);
				}
			}
		}
	}
	return(0);
}

int		handleOperatorChannelMode(Server &server, Client &client, char sign, char mode, std::string user, std::string chan )
{
	if (sign == '+')
	{
		if (mode == 'o')
		{
			server.getChannel(chan).getClientOperator().insert(server.getClientByName(user).getID());
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "+o" + "\r\n", "");
			return (0);
		}
	}
	else if (sign == '-')
	{
		if (mode == 'o')
		{
			server.getChannel(chan).getClientOperator().erase(server.getClientByName(user).getID());
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "-o" + "\r\n", "");
			return(0);
		}
	}
	else
		client.sendMsg(client.getID() + " 472 " + mode + " :is unknown mode char to me\r\n");
	return (0);
}


int		handlePasswChannelMode(Server &server, Client &client, char sign, char mode, std::string key, std::string chan )
{
	if (sign == '+')
	{
		if (mode == 'k')
		{
			server.getChannel(chan).setChannelPassw(key);
			server.getChannel(chan).setPasswMode(true);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "+k" + "\r\n", "");
			return (0);
		}
	}
	else if (sign == '-')
	{
		if (mode == 'k')
		{
			server.getChannel(chan).setPasswMode(false);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "-k" + "\r\n", "");
			return(0);
		}
	}
	else
		client.sendMsg(client.getID() + " 472 " + mode + " :is unknown mode char to me\r\n");
	return (0);
}


int		handleTopicRestrictChannelMode(Server &server, Client &client, char sign, char mode, std::string chan )
{
	if (sign == '+')
	{
		if (mode == 't')
		{
			server.getChannel(chan).setTopicLimitMode(true);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "+t" + "\r\n", "");
			return (0);
		}
	}
	else if (sign == '-')
	{
		if (mode == 't')
		{
			server.getChannel(chan).setTopicLimitMode(false);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "-t" + "\r\n", "");
			return(0);
		}
	}
	else
		client.sendMsg(client.getID() + " 472 " + mode + " :is unknown mode char to me\r\n");
	return (0);
}



int		handleSizeChannelMode(Server &server, Client &client, char sign, char mode, std::string key, std::string chan )
{

	if (sign == '+')
	{
		if (mode == 'l')
		{
			stringstream stream(key);
			if (stream.fail()) {
    			std::cout << "This is not an integer\n" << std::endl;
    			stream.clear();
    			return (0);
			}
			size_t output;
			stream >> output;
			if (server.getChannel(chan).getSizeLimit() <= static_cast<size_t>(server.getChannel(chan).getClientConnectList().size()))
			{
				std::cout << "Size Limit must be smaller than the current connected users numbers." << std::endl;
				return (0);
			}
			server.getChannel(chan).setSizeLimit(output);
			server.getChannel(chan).setSizeLimitMode(true);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "+l" + "\r\n", "");
			return (0);
		}
	}
	else if (sign == '-')
	{
		if (mode == 'l')
		{
			server.getChannel(chan).setSizeLimitMode(false);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "-l" + "\r\n", "");
			return(0);
		}
	}
	else
		client.sendMsg(client.getID() + " 472 " + mode + " :is unknown mode char to me\r\n");
	return (0);
}


int		handleInviteOnlyMode(Server &server, Client &client, char sign, char mode, std::string chan)
{
	if (sign == '+')
	{
		if (mode == 'i')
		{
			server.getChannel(chan).setInviteMode(true);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "+i" + "\r\n", "");
			return (0);
		}
	}
	else if (sign == '-')
	{
		if (mode == 'i')
		{
			server.getChannel(chan).setInviteMode(false);
			server.getChannel(chan).sendMessageToClients(client.getIDCMD() + " 324 " + client.getNickname() + " " + chan + " " + "-1" + "\r\n", "");
			return(0);
		}
	}
	else
		client.sendMsg(client.getID() + " 472 " + mode + " :is unknown mode char to me\r\n");
	return (0);
}

int		updateUserModes(Client &client, char sign, char mode)
{
	std::string character(1, mode);
	if (sign == '+')
	{
		if (mode == 'i')
		{
			client.setInvisibleMode(true);
			RPL_UMODEIS(client, "+", character);
		}
		else
		{
			if (mode !='o')
				client.sendMsg(client.getIDCMD() + " 472 " + character + " :is unknown mode char to me\r\n");
		}
	}
	else
	{
		if (mode == 'i')
		{
			client.setInvisibleMode(false);
			RPL_UMODEIS(client, "-", character);
		}
		if (mode == 'o' and client.isOperatorMode() == true)
		{
			client.setOperatorMode(false);
			RPL_UMODEIS(client, "-", character);
		}
		else if (mode != 'i' and mode != 'o')
		{
			client.sendMsg(client.getIDCMD() + " 472 " + character + " :is unknown mode char to me\r\n");
		}
	}
	return (1);
}

// CASE 1) Not enough parameter.
// CASE 2) Channel does not exist.
// CASE 3) Client asking is not on the channel.
// CASE 4) Client asking is not channel operator.
// CASE 5) If +o/-o, User we want to change mode is not on the channel.
bool	parsingErrorChannel(Server &server, Client &client, std::vector<std::string> cmd)
{
	if (cmd.size() == 1)
	{
		if (server.isChannelExisting(cmd[0]) == true)
		{
			if (server.getChannel(cmd[0]).getInviteMode() == true)
				RPL_CHANNELMODEIS(client, cmd[0], "+i");
			else
				RPL_CHANNELMODEIS(client, cmd[0], "-i");
			return (false);
		}
	}
	std::string  channelName = cmd[0];
	toLowerStr(channelName);
	if (!server.isChannelExisting(channelName))
	{
		// sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return (false);
	}
	if (cmd.size() < 2)
	{
		// sendMessage(ERR_NEEDMOREPARAMS("MODE"));
		return (false);
	}
	if (!server.getChannel(channelName).isclientConnected(client.getID()))
	{
		//sendMessage(ERR_NOTONCHANNEL(channelName));
		return (false);
	}
	if (!server.getChannel(channelName).isClientOperatorChannel(client.getID()))
	{
		// sendMessage(getPrefix() + ERR_CHANOPRIVSNEEDED(channelName, this->userInfos.nickName));
		return(false);
	}
	if (cmd.size() == 3)
	{
		if (!server.getChannel(channelName).isclientConnected(server.getClientByName(cmd[2]).getID()))
		{
			return (false);
		}
	}
	return (true);
}

void	addUserMode(Server &server, Client &client, std::vector<std::string> cmd)
{
	if (cmd.size() < 2)
	{
		// TO DO:  sendMessage(ERR_NEEDMOREPARAMS("MODE"));
		return ;
	}
	if (cmd[0].compare(client.getNickname()) != 0)
	{
		// TO DO: sendMessage(ERR_USERSDONTMATCH(this->userInfos.nickName));
		return ;
	}
	if (cmd.size() == 2)
	{
		parseModes(server, client, cmd[1], USER_MODE, "", "");
		return;
	}
	else if (cmd.size() > 2)
	{
		for (std::vector<std::string>::iterator it = cmd.begin() ; it != cmd.end(); it++)
			parseModes(server, client, *it, USER_MODE, "", "");
		return;
	}
	return;
}

void	addChannelMode(Server &server, Client &client, std::vector<std::string> cmd)
{
	if (!parsingErrorChannel(server, client, cmd))
		return;
	std::string targetName = "";
	if (cmd.size() > 3)
		targetName = cmd[2];
	parseModes(server, client, cmd[1], CHANNEL_MODE, targetName, cmd[0]);
	return;
}


void	MODE(Server &server, Client &client)
{
    Message message =  client.getClientMessage();
    if (!client.isIdentified())
    {
        return;
    }
	if (message.args.size() < 1)
	{
		client.sendMsg("461 ERR_NEEDMOREPARAMS:Invalid number of arguments.");
		return;
	}
	if (message.args[0].find("#") != std::string::npos)
		addChannelMode(server, client, message.args);
	else
		addUserMode(server, client, message.args);
	return;
}