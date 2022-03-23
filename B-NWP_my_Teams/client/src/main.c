/*
** EPITECH PROJECT, 2021
** EpitechTools
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client.h"

char *set_argument(char *cmd)
{
    int nb = 0;
    char *ret = NULL;

    for (size_t i = 0; i < strlen(cmd); i++) {
        if (cmd[i] == '\"')
            nb++;
    }
    ret = malloc((strlen(cmd) - nb + 1) * sizeof(char));
    for (size_t i = 0, n = 0; i < strlen(cmd); i++) {
        if (cmd[i] != '\"') {
            ret[n] = cmd[i];
            n++;
        }
    }
    ret[strlen(cmd) - nb] = '\0';
    return ret;
}

void send_bytes(to_send_t *msg)
{
    ssize_t size;
    void *bytes;

    size = encode_struct(msg, &bytes);
    if (bytes)
        write(3, bytes, size);
    free(bytes);
}

void free_cmd_client(client_t *client, to_send_t *msg, char *command)
{
    for (int i = 0; client->cmd[i] != NULL; ++i)
        free(client->cmd[i]);
    free(client->cmd);
    free(command);
    free(msg);
}

int main(int ac, char **av)
{
    return start(ac, av);
}