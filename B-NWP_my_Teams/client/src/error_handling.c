/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** error_handling
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include "client.h"

static bool check_ip(char *ip)
{
    for (int i = 0; ip[i] != '\0'; ++i)
        if (ip[i] != '.' && (ip[i] < '0' || ip[i] > '9')) {
            fprintf(stderr, "Error: Ip isn't valid\n");
            return true;
        }
    return false;
}

static bool check_args(char *port, char *ip)
{
    int nb = 0;

    for (size_t i = 0; i < strlen(port); ++i)
        if (port[i] < '0' || port[i] > '9')
            return true;
    for (size_t i = 0; i < strlen(ip); ++i)
        if (ip[i] == '.')
            nb++;
    if (nb != 3)
        return true;
    if (check_ip(ip))
        return true;
    return false;
}

bool error_handling(int ac, char *ip, char *port)
{
    struct hostent *info = NULL;

    if (ac != 3) {
        fprintf(stderr, "Error, retry with -help\n");
        return true;
    }
    if (check_args(port, ip))
        return true;
    info = gethostbyname(ip);
    if (!info) {
        fprintf(stderr, "Error: ip isn't valid\n");
        return true;
    }
    return false;
}