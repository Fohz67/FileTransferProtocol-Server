/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** user.c
*/

#include "my_command_type.h"

void user(client_t *client, char **args, char *path)
{
    (void)path;
    if (!CLIENT_OK(client) || !args) {
        return;
    }
    if (client->is_logged) {
        SAFE_WRITE(client->socket.fd, _503);
        return;
    }
    if (client->username) {
        free(client->username);
        client->username = NULL;
    }
    if (args[1]) {
        client->username = strdup(args[1]);
        SAFE_WRITE(client->socket.fd, _331);
    } else {
        SAFE_WRITE(client->socket.fd, _530);
    }
}
