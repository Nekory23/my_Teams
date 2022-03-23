/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** list_client
*/

#include "s_client.h"
#include <stdlib.h>

list_t *create_start(int fd)
{
    list_t *list = malloc(sizeof(client_list_t));

    list->socket_fd = fd;
    list->next = NULL;
    list->prev = NULL;
    return (list);
}

list_t *add_block(list_t *list, int fd)
{
    list_t *new = malloc(sizeof(client_list_t));

    while (list->next != NULL)
        list = list->next;
    new->socket_fd = fd;
    new->next = NULL;
    new->prev = list;
    list->next = new;
    return (list->next);
}

int del_block_start(list_t *list, client_t *client)
{
    if (list->prev == NULL && list->next == NULL) {
        free(list);
        client->start = NULL;
        return (0);
    }
    if (list->prev == NULL && list->next != NULL) {
        list->next->prev = NULL;
        client->start = list->next;
        free(list);
    }
    return (0);
}

int del_block(list_t *list, client_t *client)
{
    if (list->prev != NULL && list->next == NULL) {
        list->prev->next = NULL;
        free(list);
        return (0);
    }
    if (list->prev != NULL && list->next != NULL) {
        list->prev->next = list->next;
        list->next->prev = list->prev;
        free(list);
        return (0);
    }
    return (del_block_start(list, client));
}