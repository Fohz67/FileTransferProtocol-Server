/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_channel.h
*/

#ifndef MY_CHANNEL_H
    #define MY_CHANNEL_H

// Anonymous declarations
typedef struct client_s client_t;
typedef struct socket_s socket_t;

// Status of channels
typedef enum status_s {
    NONE,
    ACTIVE,
    PASSIVE
} status_t;

// Channel structure
typedef struct channel_s {
    int fd;
    status_t status;
    socket_t socket;
} channel_t;

// Destroy
void destroy_channel(client_t *);

// Manage
int login_channel(client_t *);

#endif
