#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"

#include <string>
#include <vector>

bool commandsHandler(Message msg, std::vector<Client> &clients, std::vector<Channel> &channels, std::string password);

#endif