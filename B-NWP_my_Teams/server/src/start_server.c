/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** connection
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

bool start_server(server_t *server, client_t *client)
{
    char *ip = inet_ntoa(server->address.sin_addr);

    FD_ZERO(&client->active_fd);
    FD_SET(server->sockfd, &client->active_fd);
    client->data = NULL;
    if (!strcmp(ip, "0.0.0.0"))
        printf("Server started on 127.0.0.1 %d\n", server->port);
    else
        printf("Server started on %s %d\n", ip, server->port);
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        return true;
    }
    return start_loop(server, client);
}