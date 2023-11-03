#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "Server.hpp"

#include <string>
#include <vector>

bool commandsHandler(Server &server, Client &client);

#endif