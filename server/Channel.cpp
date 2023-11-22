#include "Server.hpp"
#include "Channel.hpp"
#include "Message.hpp"
#include "messages.hpp"
#include "commands.hpp"
#include "utils.hpp"


Channel::Channel(Server& serv, std::string channel_name):
_server(serv), _name(channel_name), _isInviteOnly(false), _isPasswordOnly(false), _isSizeLimit(false), _isTopicLimited(false)
{
	this->_topic = "";
	this->_sizeLimit = 0;
	this->passw = "";
}

Channel::~Channel(){}

bool Channel::isClientOperatorChannel(std::string ID)
{
	if (this->_clientOperators.find(ID) != this->_clientOperators.end())
		return (true);
	return false;
}

Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		_server = other.getServer();
		_name = other.getChannelName();
		_topic = other.getTopic();
	}
	return *this;
}

std::string Channel::getChannelName() const 
{
	 return this->_name;
}

std::string Channel::getTopic() const 
{ 
	return this->_topic;
}

Server &Channel::getServer() const 
{
	 return this->_server; 
}

bool Channel::operator==(const Channel &other)  {
	return this->_name == other.getChannelName() && this->_topic == other.getTopic();
}

bool	Channel::isclientConnected(std::string ID)
{
	if (this->_clientConnected.find(ID) != this->_clientConnected.end())
		return (true);
	return false;
}

bool	Channel::isClientBanned(std::string ID)
{
	if (this->_clientBanned.find(ID) != this->_clientBanned.end())
			return (true);
	return false;
}

void Channel::addClient(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->_clientConnected.insert(client.getID());
	// messages de welcome envoyes selon norme IRC 1459 et http://chi.cs.uchicago.edu/chirc/assignment3.html7
	std::string clientList;
	for( std::set<std::string>::iterator it = this->_clientConnected.begin(); it != this->_clientConnected.end(); it++ )
	{
		if (this->isClientOperatorChannel(*it))
			clientList.append("@");
		clientList.append(*it);
		if (it != _clientConnected.end())
			clientList.append(" ");
	}
	// messages au client se connectant
	if (this->_topic == "")
		sendRplNoTopic(client, *this);
	else
		sendRplTopic(client, *this);
	sendRplNamReply(client, *this, clientList);
	sendRplEndOfNames(client, *this);
	sendMessageToClients(sendJOIN(client, this->getChannelName()), "");
	return;
}

void Channel::addOperator(std::string ID)
{
	this->_clientOperators.insert(ID);
}

void Channel::removeConnected(std::string ID)
{
	this->_clientConnected.erase(ID);
}

void Channel::removeBanned(std::string ID)
{
	this->_clientBanned.erase(ID);
}

void Channel::removeOperator(std::string ID)
{
	int	isOperatorChannel = false;
	if (this->isClientOperatorChannel(ID))
		isOperatorChannel = true;
		
	if (isOperatorChannel == true)
	{
		this->_clientOperators.erase(ID);
	}
}

// Send a message to everyone except the sender
// if sender == "" -> send to everyone
void	Channel::sendMessageToClients(std::string msg, std::string sender)
{
 	for( std::set<std::string>::iterator it = this->_clientConnected.begin(); it != this->_clientConnected.end(); it++ )
	{
		if (this->_server.getClient(*it).getNickname() != sender)
		{
			if (sendCustom(this->_server.getClient(*it).getFD() , msg.c_str(), msg.size(), 0) == -1)
				std::cout << "error sending message: " << std::endl;
		}
	}
}