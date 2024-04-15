/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** pwd.c
*/

#include "my_command_type.h"
#include "consts/my_messages.h"

static const char SLASH_STR[] = "/";

void pwd(client_t *client, char **args, char *path)
{
    char *message = NULL;

    (void)args;
    if (!CLIENT_OK(client) || !client->cwd || !path) {
        return;
    }
    message = strdup(client->cwd + strlen(path) - 1);
    if (message) {
        if (strcmp(message, SLASH_STR) != MATCH &&
            message[strlen(message) - 1] == SLASH) {
            message[strlen(message) - 1] = END_STR;
        }
        dprintf(client->socket.fd, _257, message);
        free(message);
    }
}
