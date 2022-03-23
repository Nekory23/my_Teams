/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** read_answer
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"

void get_message(client_t *st, to_send_t *msg)
{
    if (strlen(st->uuid) == 0 || st->login == false)
        st->uuid = msg->uuid;
    if (strcmp(st->uuid, msg->uuid) == 0)
        st->user = msg->username;
    if (msg->type == c_login)
        login(st, msg);
    if (msg->type == c_logout)
        logout(st, msg);
}

void read_answers(client_t *st)
{
    size_t size = 4097;
    ssize_t nb_bytes;
    char *bytes = malloc(sizeof(char) * size);
    to_send_t *msg = malloc(sizeof(to_send_t));

    if (bytes == NULL) {
        perror("malloc");
        return;
    }
    nb_bytes = read(3, bytes, 4089);
    if (nb_bytes <= 0) {
        perror("read");
        exit(0);
    }
    decode_message(bytes, nb_bytes, msg);
    get_message(st, msg);
}