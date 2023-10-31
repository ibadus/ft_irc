#include "utils.hpp"

#include <string>
#include <iostream>

std::string errNoSuchChannel() {
	return std::string(TEXT_RED + "403 ERR_NOSUCHCHANNEL:No channel found with this name." + TEXT_RESET + std::endl);
}

std::string errBannedFromChan() {
	return std::string(TEXT_RED + "474 ERR_BANNEDFROMCHAN:You are banned from this channel. You cannot /JOIN." + TEXT_RESET + std::endl);
}

std::string errInviteOnlyChan() {
	return std::string(TEXT_RED + "473 ERR_INVITEONLYCHAN:This channel is invite only." + TEXT_RESET + std::endl);
}

std::string errChannelIsFull() {
	return std::string(TEXT_RED + "471 ERR_CHANNELISFULL:The maximum number of users in this channel has been reached, thus you cannot /JOIN." + TEXT_RESET + std::endl);
}

std::string errNoSuchChannel() {
	return std::string(TEXT_RED + "403 ERR_NOSUCHCHANNEL: No channel found with this name" + TEXT_RESET + std::endl);
}