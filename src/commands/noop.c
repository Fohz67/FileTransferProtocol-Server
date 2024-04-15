/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** noop.c
*/

#include "my_command_type.h"

void noop(client_t *client, char **args, char *path)
{
    (void)client;
    (void)args;
    (void)path;
    if (!CLIENT_OK(client)) {
        return;
    }
    dprintf(client->socket.fd, _200, "NOOP");
    return;
}
