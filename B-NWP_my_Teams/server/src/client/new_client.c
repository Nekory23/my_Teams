/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** new_client
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"

static bool check_is_exist(server_t *server, client_t *client, int fd)
{
    int tmp = 0;

    if (!client->data)
        return false;
    for (tmp = 0; tmp != server->nb_client; ++tmp)
        if (client->data[tmp]->fd == fd)
            return true;
    return false;
}

static void init_new_client(data_t *data, int fd, client_t *client)
{
    data->fd = fd;
    data->is_connected = false;
    data->ip = inet_ntoa(client->address.sin_addr);
    data->addr = client->address;
    data->name = NULL;
    data->uuid = NULL;
}

bool new_client(server_t *server, client_t *client, int fd)
{
    if (check_is_exist(server, client, fd))
        return false;
    server->nb_client += 1;
    if (server->nb_client == 1 && client->start == NULL)
        client->start = create_start(fd);
    else
        add_block(client->start, fd);
    client->data = reallocarray(client->data,
    sizeof(data_t *), server->nb_client);
    if (client->data == NULL) {
        perror("reallocarray");
        return true;
    }
    client->data[server->nb_client - 1] = malloc(sizeof(data_t));
    if (client->data[server->nb_client - 1] == NULL) {
        perror("malloc");
        return true;
    }
    init_new_client(client->data[server->nb_client - 1], fd, client);
    return false;
}