#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Client.hpp"
#include "Channel.hpp"

#include <string>
#include <vector>

bool commandsHandler(std::string msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels, std::string password);

#endif