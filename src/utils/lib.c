/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** lib.c
*/

#include "my_ftp.h"
#include <sys/stat.h>
#include <stdbool.h>

size_t count_char(const char *str, char alpha)
{
    size_t counter = 0;

    for (size_t index = 0; str[index]; index++) {
        if (str[index] == alpha) {
            counter++;
        }
    }
    return counter;
}

bool is_dir(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != SUCCESS) {
        return false;
    }
    return S_ISDIR(path_stat.st_mode);
}

size_t str_length(const char *str)
{
    if (!str) {
        return SUCCESS;
    }
    return strlen(str);
}

size_t array_length(void *array)
{
    char **tab = array;
    size_t index = 0;

    if (!array) {
        return 0;
    }
    while (tab[index]) {
        index++;
    }
    return index;
}

char *concat_strings(const char *str1, const char *str2)
{
    char *concat = NULL;

    if (!str1 || !str2) {
        return NULL;
    }
    concat = malloc(strlen(str1) + strlen(str2) + 1);
    if (!concat) {
        return NULL;
    }
    strcpy(concat, str1);
    strcat(concat, str2);
    return concat;
}
