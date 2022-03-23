/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** connect_cmd
*/

#include "client.h"
#include <stdio.h>
#include <string.h>

bool login(client_t *client, to_send_t *msg)
{
    if (strcmp(client->uuid, msg->uuid) == 0)
        client->login = true;
    if (client->login == true)
        client_event_logged_in(msg->uuid, msg->username);
    return false;
}

bool logout(client_t *client, to_send_t *msg)
{
    if (client->login == false && strcmp(msg->uuid, client->uuid) == 0) {
        client_error_unauthorized();
        return false;
    }
    else if (client->login == true) {
        if (strcmp(msg->uuid, client->uuid) == 0)
            client->login = false;
        client_event_logged_out(msg->uuid, msg->username);
    }
    return true;
}

bool help_description(void)
{
    char *msg_help[17] = {"HELP :\n",
    "COMMAND :\t\t DESCRIPTION :\n",
    "\t/login [\"username\"] : login with your id\n",
    "\t/logout : disconnect the client from the server\n",
    "\t/users : get the list of all users that exist on the domain\n",
    "\t/user [\"user_uuid\"] : get informations about a user\n",
    "\t/send [\"user_uuid\"] [\"message_body\"] : send a message to a user\n",
    "\t/messages [\"user_uuid\"] : list all messages exchanged with a user\n",
    "\t/subscribe [\"team_uuid\"] : subscribe to a team\n",
    "\t/subscribed ?[\"team_uuid\"] : list all subscribed team or all users",
    " subscribed to a team\n",
    "\t/unsubscribe : unsubscribe from a team\n",
    "\t/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"] : ",
    "use specify a context team / channel / thread\n",
    "\t/create : based on what is being used and create it\n",
    "\t/list : based on what is being used and list it\n",
    "\t/info : based on what is being used and displays infos of it\n"};

    for (int i = 0; i < 16; i++)
        printf("%s", msg_help[i]);
    return false;
}