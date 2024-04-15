/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_ftp.h
*/

#ifndef MY_FTP_H
    #define MY_FTP_H

    #include "consts/my_defines.h"
    #include "consts/my_imports.h"
    #include <stdbool.h>

// Anonymous declaration for server
typedef struct server_s server_t;
typedef struct client_s client_t;

// Data handling
char *build_path(const char *, const char *, bool b);
char **transform_to_array(char *);
char *input_client(client_t *);

// Runner
int runner(const in_port_t port, char *, server_t *);

#endif
