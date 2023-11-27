#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include "Client.hpp"

#include <string>

void QUIT(Server &server, Client &client)
{
    Message message =  client.getClientMessage();   
    if (!client.isIdentified())
        return;
    if (!client.isOnline())
        return;
    std::cout << "DISCONNECT CLIENT NAME = " << client.getNickname() << std::endl;
    client.setOnline(false);
    if (message.args.size() == 1)
    {
        std::vector<Client> clientList = server.clients;
        std::string nickname = client.getNickname();
        sendQUITREASON(client, client, message.args[0]);
        for( std::vector<Client>::iterator it = clientList.begin(); it != clientList.end(); it++ )
        {
            if (server.isClientExistingID(it->getID()))
		    {
                if (it->getNickname() != nickname)
                {
                    if (message.args[0].size() != 0)
                        sendQUITREASON(*it, client, message.args[0]);
                }
            }
        }
        return;
    }
    sendQUIT(client, client);
    std::vector<Client> clientList = server.clients;
    std::string nickname = client.getNickname();
    for( std::vector<Client>::iterator it = clientList.begin(); it != clientList.end(); it++ )
    {
        if (server.isClientExistingID(it->getID()))
		{
            if (it->getNickname() != nickname)
            {
                if (message.args.size() == 0)
                    sendQUITREASON(*it, client, "");
                else 
                    sendQUIT(*it, client);
            }
        }
    }
    return;
}