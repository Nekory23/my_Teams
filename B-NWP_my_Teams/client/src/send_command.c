/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** get_command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"

static char *get_command(void)
{
    size_t size = 4096;
    char *tmp = malloc(sizeof(char) * size);

    if (getline(&tmp, &size, stdin) == EOF)
        return NULL;
    return clear_space(tmp);
}

enum types set_type_bis(char *cmd)
{
    if (strcmp(cmd, "/subscribe") == 0)
        return c_subscribe;
    if (strcmp(cmd, "/suscribed") == 0)
        return c_subscribed;
    if (strcmp(cmd, "/send") == 0)
        return c_send;
    if (strcmp(cmd, "/unsuscribe") == 0)
        return c_unsubscribe;
    if (strcmp(cmd, "/use") == 0)
        return c_use;
    if (strcmp(cmd, "/create") == 0)
        return c_create;
    if (strcmp(cmd, "/list") == 0)
        return c_list;
    if (strcmp(cmd, "/info") == 0)
        return c_info;
    return null;
}

enum types set_type(char *cmd)
{
    if (strcmp(cmd, "/help") == 0)
        return c_help;
    if (strcmp(cmd, "/login") == 0)
        return c_login;
    if (strcmp(cmd, "/logout") == 0)
        return c_logout;
    if (strcmp(cmd, "/users") == 0)
        return c_users;
    if (strcmp(cmd, "/user") == 0)
        return c_user;
    if (strcmp(cmd, "/send") == 0)
        return c_send;
    if (strcmp(cmd, "/messages") == 0)
        return c_messages;
    return (set_type_bis(cmd));
}

bool set_msg(client_t *client, to_send_t *msg)
{
    msg->type = set_type(client->cmd[0]);
    if (msg->type == null) {
        printf("Unknow command.\n");
        return false;
    }
    if (msg->type != c_login && msg->type != c_logout)
        return false;
    msg->username = client->user;
    msg->uuid = client->uuid;
    msg->logged_in = client->login;
    msg->size = 0;
    if (client->cmd[1] != NULL && msg->type != c_login) {
        msg->size = strlen(client->cmd[1]);
        memcpy(msg->data, client->cmd[1], msg->size);
    } else if (msg->type == c_login && client->cmd[1] != NULL)
        msg->username = set_argument(client->cmd[1]);
    return true;
}

bool send_commands(client_t *client)
{
    char *command = get_command();
    to_send_t *msg = malloc(sizeof(to_send_t));

    if (command == NULL)
        return true;
    if (strcmp(command, "/help") == 0)
        return help_description();
    client->cmd = split_cmd(command, ' ');
    if (set_msg(client, msg) == false)
        return false;
    if (client->cmd[1] == NULL && msg->type == c_login) {
        free_cmd_client(client, msg, command);
        printf("You must enter a login.\n");
        return false;
    }
    send_bytes(msg);
    free_cmd_client(client, msg, command);
    return false;
}