#include "utils.hpp"
#include <string>
#include <sstream>

int toInt(std::string s) {
	int n;
	std::stringstream ss(s);

	ss >> n;
	return n;
}

std::vector<std::string> split(std::string str, std::string separator)
{
	std::vector<std::string> output;
	std::string	sub_str;
	size_t	pos = 0;

	if (str.empty())
		return (output);
	while ((pos = str.find(separator)) != std::string::npos)
	{
		sub_str = str.substr(0, pos);
		output.push_back(sub_str);
		str.erase(0, pos + 1);
	}
	if (!str.empty())
		output.push_back(str);
	return (output);
}

void toLowerStr(std::string& str)
{
	for(std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		*it = tolower(*it);
	}
}

bool isChannelFlag(char flag)
{
	if (flag == '&' || flag == '#' || flag == '+' || flag == '?')
		return (true);
	return (false);
}

bool isChannelName(std::string str)
{
	if (str.size() == 0 || str.size() == 1 || str.size() > 50)
		return (false);
	if (str.find(" ") !=  std::string::npos || str.find(7) !=  std::string::npos || str.find(',') !=  std::string::npos)
		return (false);
	if (!isChannelFlag(str[0]))
		return (false);
	return (true);
}


ssize_t sendCustom(int sockfd, const void *buf, size_t len, int flags)
{
	std::string msg;
	const char* pt;
	pt = static_cast <const char*> (buf);
	for (size_t i = 0; i < len ; i++)
	{
		if (pt[i] == '\r')
		{
			msg.push_back('\\');
			msg.push_back('r');
		}
		else if (pt[i] == '\n')
		{
			msg.push_back('\\');
			msg.push_back('n');
		}
		else
			msg.push_back(pt[i]);
	}
	std::cout << " => Message sent to fd " << sockfd << ": -->" << msg << "<--" << std::endl;
	return(send(sockfd, buf, len, flags));
}