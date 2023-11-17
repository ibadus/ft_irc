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
    client.setOnline(false);
    if (message.args.size() == 1)
    {
       sendQUITREASON(client, message.args[0]);
       sendQuitToAllExceptUser(server, client, message.args[0]);
       return;
    }
    sendQUIT(client);
    sendQuitToAllExceptUser(server, client, "");
    return;
}