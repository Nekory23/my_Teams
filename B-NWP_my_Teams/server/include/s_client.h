/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

/* INCLUDES */
#include <stddef.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdbool.h>

/* STRUCTURES */

typedef struct client_list {
    int socket_fd;
    struct client_list *next;
    struct client_list *prev;
}client_list_t;

typedef client_list_t list_t;

typedef struct data_s
{
    int fd;
    char *ip;
    bool is_connected;
    char **cmd;
    char *uuid;
    char *name;
    struct sockaddr_in addr;
} data_t;

typedef struct client_s {
    int sockfd;
    struct sockaddr_in address;
    fd_set active_fd;
    fd_set read_fd;
    data_t **data;
    list_t *start;
} client_t;

#endif /* !CLIENT_H_ */