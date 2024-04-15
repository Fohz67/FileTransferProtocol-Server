/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** pass.c
*/

#include "my_command_type.h"

static const char A[] = ANONYMOUS_NAME;

void pass(client_t *client, char **args, char *path)
{
    (void)path;
    if (!CLIENT_OK(client) || !args) {
        return;
    }
    if (!client->username || client->is_logged) {
        SAFE_WRITE(client->socket.fd, _503);
        return;
    }
    if (client->password) {
        free(client->password);
    }
    client->password = strdup(args[1] ? args[1] : EMPTY);
    if (!strcmp(client->username, A) && !strcmp(client->password, EMPTY)) {
        SAFE_WRITE(client->socket.fd, _230);
        client->is_logged = true;
    } else {
        SAFE_WRITE(client->socket.fd, _530);
        free(client->password);
        client->password = NULL;
    }
}
