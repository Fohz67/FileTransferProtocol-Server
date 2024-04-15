/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** cdup.c
*/

#include "my_command_type.h"

static const char COMMAND_NAME[] = "CDUP";
static const char DIR_BACK[] = "../";

void cdup(client_t *client, char **args, char *path)
{
    char *cwd = NULL;

    (void)args;
    if (!CLIENT_OK(client) || !path || !client->cwd) {
        return;
    }
    if (strcmp(path, client->cwd) == SUCCESS) {
        dprintf(client->socket.fd, _200, COMMAND_NAME);
        return;
    }
    cwd = build_path(client->cwd, DIR_BACK, true);
    if (cwd) {
        free(client->cwd);
        client->cwd = cwd;
        dprintf(client->socket.fd, _200, COMMAND_NAME);
    } else {
        SAFE_WRITE(client->socket.fd, _550);
    }
}
