/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** init_server
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

static bool gest_error(server_t *server, char *error)
{
    if (error != NULL)
        perror(error);
    close(server->sockfd);
    shutdown(server->sockfd, SHUT_RDWR);
    return true;
}

static void fill_address(server_t *server)
{
    server->address.sin_family = PF_INET;
    server->address.sin_port = htons(server->port);
    server->address.sin_addr.s_addr = htonl(INADDR_ANY);
    server->size_addr = sizeof(server->address);
    server->size_socket = sizeof(server->sockfd);
}

static bool end_of_init(server_t *s)
{
    if (bind(s->sockfd, (struct sockaddr *)&s->address, s->size_addr) == -1)
        return gest_error(s, "bind");
    s->queue = listen(s->sockfd, MAX_CLIENT);
    if (s->queue == -1)
        return gest_error(s, "listen");
    s->nb_client = 0;
    return false;
}

bool init_server(server_t *s, char *arg)
{
    int check = 0;

    s->port = atoi(arg);
    if (s->port < 1 || s->port > 65534) {
        printf("Error: port isn't valid\n");
        return true;
    }
    s->sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (s->sockfd == -1)
        return gest_error(s, "socket");
    fill_address(s);
    check = setsockopt(s->sockfd, SOL_SOCKET, SO_REUSEADDR, &s->address,
    sizeof(int));
    if (check == -1)
        return gest_error(s, "setsockopt");
    return end_of_init(s);
}