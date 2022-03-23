/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** start
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

static int display_help(char *prog)
{
    printf("USAGE: %s port\n\n", prog);
    printf("       port\tis the port number on which");
    printf(" the server socket listens.\n");
    return SUCCESS;
}

static bool error_handling(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, STR_ERROR);
        fprintf(stderr, ERR_ARG_NBR);
        return true;
    }
    for (int i = 0; av[1][i] != '\0'; ++i)
        if (av[1][i] < '0' || av[1][i] > '9') {
            fprintf(stderr, STR_ERROR);
            fprintf(stderr, ERR_PORT);
            return true;
        }
    return false;
}

int start(int ac, char **av)
{
    server_t server;
    client_t client;

    if (ac == 2 && !strcmp(av[1], "-help"))
        return display_help(av[0]);
    if (error_handling(ac, av))
        return ERROR;
    if (init_server(&server, av[1]) || start_server(&server, &client))
        return ERROR;
    end_server(&server, &client);
    return SUCCESS;
}