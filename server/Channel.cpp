#include "channel.hpp"

Channel::Channel(Server& serv, std::string channel_name):
server(serv), ID(channel_name), isInviteOnly(false)
{
	//this->topic = "Welcome to the channel " + channel_name + " !!";
	this->topic = "";
}

Channel::~Channel(){}

bool Channel::isClientOperatorChannel(std::string ID)
{
	if (this->_clientOperators.find(ID) != this->_clientOperators.end())
		return (true);
	return false;
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

// fonction prenant initialement un objet Client en argument, c'est pour ca qu'elle est codé de cette facon
void Channel::addClient(std::string ID)
{
	Client& client = *(this->server.getClient(ID));
	this->_clientConnected.insert(client.getID);
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
	if (this->topic == "")
		// SEND NONE TOPIC  RPL client.sendMsg();
	else
		// send differents RPL MESSAGES
	
	// annonce arrivée aux autres clients
	//SEND MESSAGES TO ALL THE CLIENTS USING JOIN PROTOCOL
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

// fonction prenant initialement un objet Client en argument, c'est pour ca qu'elle est codé de cette facon
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
		if (this->server.getClient(*it)->userInfos.nickName != sender)
		{
			// send message to specific fd
		}
	}
}