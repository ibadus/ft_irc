#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"

#include <string>
#include <vector>

void sendRplWelcome(Server &server, Client &client);
void sendNick(Client &client);
void sendPONG(Server &server);
void sendPING(Client &client, Message &message);
void PASS(Server &server, Client &client);
void PING(Client &client);
void NICK(Server &server, Client &client);
void USER(Server &server, Client &client);

#endif