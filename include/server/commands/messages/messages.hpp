#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"

#include <string>
#include <vector>

void PASS(Message &msg, std::string password);
void PING(Message &msg);
void NICK(Message msg, std::vector<Client> &clients);

#endif