/*
** EPITECH PROJECT, 2021
** EpitechTools
** File description:
** main
*/

#ifndef CLIENT_H_
#define CLIENT_H_

/* INCLUDE */
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <uuid/uuid.h>
#include <arpa/inet.h>
#include <signal.h>

#include "../../libs/myteams/logging_client.h"
#include "struct.h"

/* STRUCTURES */
typedef struct client_s
{
    int sockfd;
    struct sockaddr_in servaddr;
    bool login;
    char *user;
    char *uuid;
    char **cmd;
    fd_set fd;
} client_t;

/* PROTOTYPES */
int start(int ac, char **av);
bool error_handling(int ac, char *ip, char *port);
bool start_client(client_t *st, char *port_arg, char *ip_arg);
char **split_cmd(char *src, char c);
void end_client(client_t *client);
bool help_description();

bool send_commands(client_t *client);
void read_answers(client_t *st);
char *clear_space(char *src);
void free_cmd_client(client_t *client, to_send_t *msg, char *command);
void send_bytes(to_send_t *msg);
char *set_argument(char *cmd);

/* BINARY PROTOTYPE */
ssize_t encode_struct(void *src, void **result);
ssize_t decode_message(const char *bytes, ssize_t length, to_send_t *st);

/* PROTOTYPES COMMANDES */

bool login(client_t *client, to_send_t *msg);
bool logout(client_t *client, to_send_t *msg);

//FUNCTIONS POINTER
typedef struct cmd_s
{
    const char *cmd;
    bool (*func_ptr)(client_t *client, to_send_t *msg);
} cmd_t;

static const cmd_t all_cmd[] =
{
    {"/login\0", &login},
    {"/logout\0", &logout},
    {NULL, NULL}
};

/* STATIC CONST */
static const int SUCCESS = 0;
static const int FAIL = 1;
static const int ERROR = 84;

static volatile sig_atomic_t run = 1;

static const int MAX_NAME_LENGTH = 32;
static const int MAX_DESCRIPTION_LENGTH = 255;
static const int MAX_BODY_LENGTH = 512;

#endif /* !MAIN_H_ */