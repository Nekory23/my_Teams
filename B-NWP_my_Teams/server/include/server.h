/*
** EPITECH PROJECT, 2021
** EpitechTools
** File description:
** main
*/

#ifndef MAIN_H_
#define MAIN_H_

/* INCLUDE */
#include <stdbool.h>
#include <netinet/in.h>
#include <signal.h>
#include <uuid/uuid.h>

/* LOCAL INCLUDE */
#include "../../libs/myteams/logging_server.h"
#include "s_client.h"
#include "struct.h"

/* STRUCTURE */
typedef struct server_s {
    int port;
    int sockfd;
    int queue;
    struct sockaddr_in address;
    socklen_t size_addr;
    socklen_t size_socket;
    int nb_client;
} server_t;

/* PROTOTYPES */
int start(int ac, char **av);
bool init_server(server_t *server, char *arg);

bool start_server(server_t *server, client_t *client);
bool start_loop(server_t *server, client_t * client);

bool handle_client(server_t *server, client_t *client);
bool handle_cmd(server_t *server, client_t *client, data_t *data);
bool new_client(server_t *server, client_t *client, int fd);

char *clear_space(char *src);
char **split_cmd(char *src, char c);

void end_server(server_t *server, client_t *client);

/* PROTOTYPES COMMANDES */

//void help(data_t *data, to_send_t *msg);
void login(data_t *data, to_send_t *msg, client_t *client);
void logout(data_t *data, to_send_t *msg, client_t *client);

/* BINARY PROTOTYPE */
ssize_t encode_struct(void *src, void **result);
ssize_t decode_message(const char *bytes, ssize_t length, to_send_t *st);

/* LIST PROTOTYPE */
list_t *create_start(int fd);
list_t *add_block(list_t *list, int fd);
int del_block_start(list_t *list, client_t *client);
int del_block(list_t *list, client_t *client);

// new ptr
typedef struct all_cmd_s {
    enum types type;
    void (*func_ptr)(data_t *data, to_send_t *msg, client_t *client);
} all_cmd_t;

static const all_cmd_t commands[] =
{
    {c_login, &login},
    {c_logout, &logout},
    {null, NULL}
};

/* STATIC CONST */
static const char STR_ERROR[] = "Error: ";
static const char ERR_ARG_NBR[] = "This program takes 1 argument.\n";
static const char ERR_PORT[] = "Argument must be a port number.\n";

static const int SUCCESS = 0;
static const int FAIL = 1;
static const int ERROR = 84;

static volatile sig_atomic_t run = 1;

static const int MAX_CLIENT = 10;

static const int MAX_NAME_LENGTH = 32;
static const int MAX_DESCRIPTION_LENGTH = 255;
static const int MAX_BODY_LENGTH = 512;

#endif /* !MAIN_H_ */
