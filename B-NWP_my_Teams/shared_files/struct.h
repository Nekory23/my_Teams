/*
** EPITECH PROJECT, 2021
** B-NWP_myTeams
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <stddef.h>

/* ENUM */
enum types {
    c_help,
    c_login,
    c_logout,
    c_users,
    c_user,
    c_send,
    c_messages,
    c_subscribe,
    c_subscribed,
    c_unsubscribe,
    c_use,
    c_create,
    c_list,
    c_info,
    null
};

/* STRUCTURES */
typedef struct to_send_s {
    enum types type;
    unsigned short size;
    char *username;
    char *uuid;
    bool logged_in;
    char data[0];
} to_send_t;

#endif /* !STRUCT_H_ */