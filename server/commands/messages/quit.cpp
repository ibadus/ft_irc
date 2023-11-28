#include "messages.hpp"
#include "Message.hpp"
#include "utils.hpp"
#include <algorithm>
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
        std::vector<Channel> channelList = server.channels;
        std::string nickname = client.getNickname();
        sendQUITREASON(client, client, message.args[0]);
        // SENDING A QUIT MESSAGE TO ALL THE USERS IN ITS CHANNEL
        for( std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); it++ )
        {
            if (it->isclientConnected(client.getID()))
            {
                for( std::set<std::string>::iterator clientCon = it->clientConnected.begin(); clientCon != it->clientConnected.end(); clientCon++ )
                {
                    if (server.isClientExistingID(*clientCon))
                    {
                        if (server.getClient(*clientCon).getNickname() != nickname)
                        {
                            if (message.args[0].size() != 0)
                                sendQUITREASON(server.getClient(*clientCon), client, message.args[0]);
                        }
                    }      
                }
            }
        }
        return ;
    }
    sendQUIT(client, client);
    std::vector<Client> clientList = server.clients;
    std::vector<Channel> channelList = server.channels;
    std::string nickname = client.getNickname();
      // SENDING A QUIT MESSAGE TO ALL THE USERS IN ITS CHANNEL
    for( std::vector<Channel>::iterator it = channelList.begin(); it != channelList.end(); it++ )
    {
        if (it->isclientConnected(client.getID()))
        {
            for( std::set<std::string>::iterator clientCon = it->clientConnected.begin(); clientCon != it->clientConnected.end(); clientCon++ )
            {
                if (server.isClientExistingID(*clientCon))
                {
                    if (server.getClient(*clientCon).getNickname() != nickname)
                    {
                        if (message.args[0].size() == 0)
                            sendQUITREASON(server.getClient(*clientCon), client, "");
                    }
                } 
            }
        }
    }
    return;
}