/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** end_client
*/

#include <unistd.h>
#include "client.h"

void end_client(client_t *client)
{
    close(client->sockfd);
    shutdown(client->sockfd, SHUT_RDWR);
}