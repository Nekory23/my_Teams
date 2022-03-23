/*
** EPITECH PROJECT, 2021
** myTeams
** File description:
** split_cmd
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char *add_char(char *str, char *src, int pos, int size)
{
    str = realloc(str, sizeof(char) * size+1);
    str[size] = src[pos];
    return str;
}

static int count_char(char *src, char c)
{
    int nb = 1;

    for (int i = 0; src[i] != '\0'; ++i)
        if (src[i] == c)
            ++nb;
    return nb;
}

static char **copy_str(char **str, char *src)
{
    str = reallocarray(str, sizeof(char *), 2);
    str[0] = strdup(src);
    str[1] = NULL;
    return str;
}

static char **split(char **str, char *src, char c)
{
    int k = 0;

    for (int i = 0, j = 0; src[i] != '\0'; ++i, ++j) {
        if (src[i + 1] == '\0') {
            str[k] = add_char(str[k], src, i, j);
            ++j;
            str[k] = add_char(str[k], "\0", 0, j);
            break;
        }
        if (src[i] == c) {
            str[k] = add_char(str[k], "\0", 0, j);
            ++k;
            j = -1;
            continue;
        }
        str[k] = add_char(str[k], src, i, j);
    }
    str[++k] = NULL;
    return str;
}

char **split_cmd(char *src, char c)
{
    int size = count_char(src, c);
    char **str = malloc(sizeof(char *) * (size + 1));

    if (size == 1)
        return copy_str(str, src);
    for (int i = 0; i != size; ++i)
        str[i] = malloc(sizeof(char) * 1);
    return split(str, src, c);
}