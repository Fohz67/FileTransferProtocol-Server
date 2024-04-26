/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** dele.c
*/

#include "my_command_type.h"

void dele(client_t *client, char **args, char *path)
{
    char *to_delete = NULL;

    if (!CLIENT_OK(client) || !args || !args[1] || !path) {
        return;
    }
    if (args[1][0] == SLASH) {
        to_delete = build_path(path, &args[1][1], false);
    } else {
        to_delete = build_path(client->cwd, args[1], false);
    }
    if (!to_delete) {
        SAFE_WRITE(client->socket.fd, _550);
        return;
    }
    if (remove(to_delete) == FAIL) {
        SAFE_WRITE(client->socket.fd, _550);
    } else {
        SAFE_WRITE(client->socket.fd, _250);
    }
    free(to_delete);
}
