/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** print.c
*/

#include "my_ftp.h"

int output_error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    return FAIL;
}

void *output_null_error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    return NULL;
}

int output_helper(void)
{
    puts("USAGE: ./myftp port path");
    puts("\tport is the port number on which the server socket listens");
    puts("\tpath is the path to the home directory for the Anonymous user");
    return SUCCESS;
}
