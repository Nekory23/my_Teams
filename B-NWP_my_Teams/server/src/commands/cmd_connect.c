/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** cmd_connect
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static void create_user(data_t *data, to_send_t *msg, client_t *client)
{
    uuid_t uuid_type;
    char *uuid = malloc(37 * sizeof(char));
    void *bytes;
    ssize_t size;
    list_t *current = client->start;

    uuid_generate_random(uuid_type);
    uuid_unparse_upper(uuid_type, uuid);
    msg->logged_in = true;
    msg->uuid = uuid;
    data->uuid = uuid;
    data->name = msg->username;
    msg->size = 0;
    server_event_user_created(uuid, data->name);
    server_event_user_logged_in(uuid);
    size = encode_struct(msg, &bytes);
    for (;current != NULL; current = current->next)
        write(current->socket_fd, bytes, size);
}

void login(data_t *data, to_send_t *msg, client_t *client)
{
    (void) client;
    create_user(data, msg, client);
    data->is_connected = true;
}

void logout(data_t *data, to_send_t *msg, client_t *client)
{
    void *bytes;
    ssize_t size;
    list_t *current = client->start;

    if (msg->logged_in == true) {
        server_event_user_logged_out(data->uuid);
        msg->size = 0;
        msg->logged_in = false;
        size = encode_struct(msg, &bytes);
        for (;current != NULL; current = current->next)
            write(current->socket_fd, bytes, size);
    }
}