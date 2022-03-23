/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** handle_cmd
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

static bool gest_error(char *error)
{
    perror(error);
    return true;
}

static bool read_cmd(data_t *data, to_send_t *msg)
{
    size_t size = 4097;
    char *bytes = malloc(sizeof(char) * size);
    ssize_t size_bytes = 0;

    if (bytes == NULL)
        return gest_error("malloc");
    bytes = memset(bytes, '\0', size);
    size_bytes = read(data->fd, bytes, 4089);
    if (size_bytes < 0)
        return gest_error("read");
    decode_message(bytes, size_bytes, msg);
    free(bytes);
    return false;
}

bool handle_cmd(server_t *server, client_t *client, data_t *data)
{
    int i = 0;
    to_send_t *msg = malloc(sizeof(to_send_t));

    (void) server;
    (void) client;
    if (read_cmd(data, msg))
        return true;
    for (i = 0; commands[i].type != null; ++i) {
        if (msg->type == commands[i].type) {
            commands[i].func_ptr(data, msg, client);
            break;
        }
    }
    return false;
}