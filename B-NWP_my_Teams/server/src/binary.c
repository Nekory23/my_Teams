/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** Binary functions
*/

#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

static ssize_t end_encode_struct(void *current, size_t user_l, size_t uuid_l,
    to_send_t *head)
{
    memcpy(current, head->username, user_l);
    current += user_l;
    *((size_t *) current) = uuid_l;
    current += sizeof(size_t);
    memcpy(current, head->uuid, uuid_l);
    current += uuid_l + sizeof(bool);
    *((size_t *) current) = head->size;
    memcpy(current, head->data, head->size);
    return (sizeof(to_send_t) + (user_l + uuid_l + head->size) * sizeof(char));
}

ssize_t encode_struct(void *src, void **result)
{
    to_send_t *header = (to_send_t *) src;
    size_t username_length = strlen(header->username);
    size_t uuid_length = strlen(header->uuid);
    void *current;

    *result = calloc(1, sizeof(to_send_t) +
    (username_length + uuid_length + header->size) * sizeof(char));
    if (!*result)
        return -1;
    current = *result;
    *((enum types *) current) = header->type;
    current += sizeof(enum types);
    *((unsigned short *) current) = header->size;
    current += sizeof(unsigned short);
    *((size_t *) current) = username_length;
    current += sizeof(size_t);
    return end_encode_struct(current, username_length, uuid_length, header);
}

ssize_t decode_str(const char *bytes, size_t length, char **result)
{
    size_t str_len;

    if (!bytes || length < sizeof(size_t) || !result)
        return -1;
    str_len = *((size_t *) bytes);
    if (!str_len) {
        *result = 0;
        return sizeof(size_t);
    }
    *result = calloc(1, (str_len + 1) * sizeof(char));
    if (!*result)
        return -1;
    (*result)[str_len] = 0;
    memcpy(*result, bytes + sizeof(size_t), str_len);
    return (sizeof(size_t) + str_len);
}

ssize_t decode_header(const char *bytes, size_t length, to_send_t *result)
{
    const char *current = bytes;
    ssize_t temp;

    result->type = *((enum types *) current);
    current += sizeof(enum types);
    result->size = *((unsigned short *) current);
    current += sizeof(unsigned short);
    temp = decode_str(current, (size_t)
    (length - (current - bytes)), &result->username);
    if (temp == -1)
        return -1;
    current += temp;
    temp = decode_str(current, (size_t)
    (length - (current - bytes)), &result->uuid);
    if (temp == -1)
        return -1;
    current += temp;
    result->logged_in = ((bool) current);
    current += sizeof(bool);
    return (ssize_t) (current - bytes);
}

ssize_t decode_message(const char *bytes, ssize_t length, to_send_t *st)
{
    ssize_t header_len;
    ssize_t str_len;

    if (!st)
        return -1;
    header_len = decode_header(bytes, length, st);
    if (header_len == -1) {
        free(st);
        return -1;
    }
    if (!st->size)
        str_len = 0;
    else
        str_len = decode_str((bytes + header_len),
        st->size, (char **) &st->data);
    if (str_len == -1) {
        free(st);
        return -1;
    }
    return (header_len + str_len);
}