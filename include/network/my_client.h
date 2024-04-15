/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_client.h
*/

#ifndef MY_CLIENT_H
    #define MY_CLIENT_H

    #include <stdbool.h>
    #include "my_channel.h"

// Anonymous declarations
typedef struct server_s server_t;
typedef struct socket_s socket_t;

// Client structure
typedef struct client_s {
    char *username;
    char *password;
    char *buffer;
    char *cwd;
    bool is_logged;
    socket_t socket;
    channel_t channel;
} client_t;

// Destroy
void remove_specific_client(client_t *);
void destroy_specific_client(client_t *);

// Alloc
void add_new_client(server_t *);
int pre_alloc_clients(server_t *);
client_t *alloc_new_client(socket_t *, char *, bool b);

// Manage
void check_fds(server_t *, int);
void check_each_fds(server_t *);

#endif
