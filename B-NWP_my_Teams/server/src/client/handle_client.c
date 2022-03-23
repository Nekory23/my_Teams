/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** handle_client
*/

#include <stdio.h>
#include "server.h"

static int find_client(server_t *server, client_t *client, int fd)
{
    int tmp = 0;

    for (tmp = 0; tmp != server->nb_client; ++tmp)
        if (client->data[tmp]->fd == fd)
            break;
    return tmp;
}

static bool set_client(server_t *server, client_t *client, int fd)
{
    int customer = 0;

    if (new_client(server, client, fd))
        return true;
    customer = find_client(server, client, fd);
    if (handle_cmd(server, client, client->data[customer]))
        return true;
    return false;
}

static bool loop_fd(server_t *server, client_t *client, int fd)
{
    if (fd == server->sockfd) {
        client->sockfd = accept(server->sockfd,
        (struct sockaddr *)&client->address, &server->size_socket);
        if (client->sockfd == -1) {
            perror("accept");
            return true;
        }
        FD_SET(client->sockfd, &client->active_fd);
    }
    else if (client->sockfd != -1)
        if (set_client(server, client, fd))
            return true;
    return false;
}

bool handle_client(server_t *server, client_t *client)
{
    for (int fd = 0; fd != FD_SETSIZE; ++fd)
        if (FD_ISSET(fd, &client->read_fd))
            if (loop_fd(server, client, fd))
                return true;
    return false;
}