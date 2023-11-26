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
	this->_passwd = "";
}

Channel::~Channel(){}

bool Channel::isClientOperatorChannel(std::string ID)
{
	if (this->clientOperators.find(ID) != this->clientOperators.end())
		return (true);
	return false;
}

bool Channel::isClientInvited(std::string ID)
{
	if (this->clientInvited.find(ID) != this->clientInvited.end())
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
	if (this->clientConnected.find(ID) != this->clientConnected.end())
		return (true);
	return false;
}

bool	Channel::isClientBanned(std::string ID)
{
	if (this->clientBanned.find(ID) != this->clientBanned.end())
			return (true);
	return false;
}


void Channel::addClient(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientConnected.insert(client.getID());
	// messages de welcome envoyes selon norme IRC 1459 et http://chi.cs.uchicago.edu/chirc/assignment3.html7
	std::string clientList;
	for( std::set<std::string>::iterator it = this->clientConnected.begin(); it != this->clientConnected.end(); it++ )
	{
		if (this->isClientOperatorChannel(*it))
			clientList.append("@");
		clientList.append(*it);
		if (it != clientConnected.end())
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
	Client& client = this->_server.getClient(ID);
	this->clientOperators.insert(client.getID());
}

void Channel::addInvited(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientInvited.insert(client.getID());
}

void Channel::addBanned(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientBanned.insert(client.getID());
}

void Channel::addConnected(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientConnected.insert(client.getID());
}


void Channel::removeInvited(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientInvited.erase(client.getID());
}

void Channel::removeConnected(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientConnected.erase(client.getID());
}

void Channel::removeBanned(std::string ID)
{
	Client& client = this->_server.getClient(ID);
	this->clientBanned.erase(client.getID());
}

void Channel::removeOperator(std::string ID)
{
	Client& client = this->_server.getClient(ID);

	int	isOperatorChannel = false;
	if (this->isClientOperatorChannel(client.getID()))
		isOperatorChannel = true;
		
	if (isOperatorChannel == true)
	{
		this->clientOperators.erase(client.getID());
	}
}

// Send a message to everyone except the sender
// if sender == "" -> send to everyone
void	Channel::sendMessageToClients(std::string msg, std::string sender)
{
 	for( std::set<std::string>::iterator it = this->clientConnected.begin(); it != this->clientConnected.end(); it++ )
	{
		if (this->_server.getClient(*it).getNickname() != sender)
		{
			if (sendCustom(this->_server.getClient(*it).getFD() , msg.c_str(), msg.size(), 0) == -1)
				std::cout << "error sending message: " << std::endl;
		}
	}
}