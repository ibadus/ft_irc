#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sys/types.h>
#include <iostream>
#include <sys/socket.h>

#define TEXT_GREEN "\033[0;32m"
#define TEXT_RED "\033[0;31m"
#define TEXT_YELLOW "\033[0;33m"
#define TEXT_BLUE "\033[1;34m"
#define TEXT_RESET "\033[m"

#define TEXT_UNDERLINE "\033[4m"
#define TEXT_BOLD "\033[1m"

int toInt(std::string s);
std::vector<std::string> split(std::string str, std::string separator);
void toLowerStr(std::string& str);
ssize_t sendCustom(int sockfd, const void *buf, size_t len, int flags);
bool isChannelFlag(char flag);
bool isChannelName(std::string str);

#endif