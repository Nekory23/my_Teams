/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** server_loop
*/

#include <stdio.h>
#include <errno.h>
#include "server.h"

static void handle_sig(int sig)
{
    (void) sig;
    run = 0;
}

bool start_loop(server_t *server, client_t * client)
{
    if (signal(SIGINT, handle_sig) == SIG_ERR) {
        perror("signal");
        return true;
    }
    client->start = NULL;
    while (run != 0) {
        client->read_fd = client->active_fd;
        if (select(FD_SETSIZE, &client->read_fd, NULL, NULL, NULL) < 0) {
            if (errno == EINTR)
                continue;
            perror("select");
            break;
        }
        if (handle_client(server, client))
            return true;
    }
    return false;
}