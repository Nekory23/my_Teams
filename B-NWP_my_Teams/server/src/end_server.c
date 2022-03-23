/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** end_server
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static void free_client(client_t *client, int nb_client)
{
    close(client->sockfd);
    client->start = NULL;
    if (client->data != NULL) {
        for (int i = 0; i != nb_client; ++i)
            free(client->data[i]);
        free(client->data);
    }
}

void end_server(server_t *server, client_t *client)
{
    printf("SERVER SHUTDOWN\n");
    close(server->sockfd);
    shutdown(server->sockfd, SHUT_RDWR);
    free_client(client, server->nb_client);
}