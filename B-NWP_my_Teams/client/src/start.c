/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** start
*/

#include <stdio.h>
#include <string.h>
#include "client.h"

static int display_help(char *prog)
{
    printf("USAGE: %s ip port\n", prog);
    printf("       ip\tis the server ip address");
    printf("on which the server socket listens\n");
    printf("       port\tis the port number on which");
    printf(" the server socket litsens\n");
    return SUCCESS;
}

int start(int ac, char **av)
{
    client_t st;

    if (ac == 2 && !strcmp(av[1], "-help"))
        return display_help(av[0]);
    if (error_handling(ac, av[1], av[2]))
        return ERROR;
    if (start_client(&st, av[2], av[1]))
        return ERROR;
    return SUCCESS;
}