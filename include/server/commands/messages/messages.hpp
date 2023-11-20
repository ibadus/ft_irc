#pragma once

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"

#include <string>
#include <vector>

void sendRplWelcome(Server &server, Client &client);
void sendNick(Client &client);
void sendPONG(Server &server, Client &client);
void sendPING(Client &client, Message &message);
void PASS(Server &server, Client &client);
void QUIT(Server &server, Client &client);
void PING(Server &server, Client &client);
void PONG(Client &client);
void OPER(Client &client);
void NICK(Server &server, Client &client);
void JOIN(Server &server, Client &client);
void USER(Server &server, Client &client);
void	NOTICE(Server &server, Client &client);
void	INVITE(Server &server, Client &client);
void	WHOIS(Server &server, Client &client);
void	PART(Server &server, Client &client);
void    KICK(Server &server, Client &client);
void	NAMES(Server &server, Client &client);
void	PRIVMSG(Server &server, Client &client);
std::string sendJOIN(Client &client, std::string chanName);
bool	isValidParsingINVITE(Server &server, Client &client);
void sendRplTopic(Client &client, Channel &channel);
void sendRplNoTopic(Client &client, Channel &channel);
bool	isValidParsingKICK(Server &server, Client &client);
void sendRplNamReply(Client &client, Channel &channel, std::string clientList);
void sendRplEndOfNames(Client &client, Channel &channel);
void sendQuitToAllExceptUser(Server &server, Client &client, std::string reason);
void sendQUIT(Client &client);
void	printMode(Client &client);
void sendPARTREASON(Server &server, Client &client, std::string channel_name, std::string reason);
void sendPART(Server &server, Client &client, std::string channel_name);
void sendQUITREASON(Client &client, std::string message);
void RPL_WHOISUSER(Client &client);
void RPL_UMODEIS(Client &client, std::string mode, std::string type);
void RPL_YOUREOPER(Client &client);
void RPL_NAMREPLY2(Client &client, std::string nickName, std::string channelName);
void RPL_ENDOFNAMES2(Client &client, std::string channelName);
void RPL_INVITING(Client &client, std::string invitenick, std::string channel);