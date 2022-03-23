/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** clear_space
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *add_char(char *str, char *src, int pos, int size)
{
    str = realloc(str, sizeof(char) * size);
    str[size-1] = src[pos];
    return str;
}

static char *replace_tab(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (str[i] == '\t')
            str[i] = ' ';
    return str;
}

char *clear_space(char *src)
{
    char *str = malloc(sizeof(char) * 1);
    int j = 0;

    src = replace_tab(src);
    for (int i = 0; src[i] != '\0'; ++i) {
        if (src[i] == ' ' && src[i+1] != ' ' && j != 0)
            str = add_char(str, src, i, ++j);
        if (src[i] == '\r' || src[i] == '\n')
            continue;
        if (src[i] != ' ')
            str = add_char(str, src, i, ++j);
    }
    if (str[j-1] == ' ')
        str[j-1] = '\0';
    else
        str = add_char(str, "\0", 0, ++j);
    return str;
}