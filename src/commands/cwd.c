/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** cwd.c
*/

#include "my_command_type.h"
#include "my_utils.h"

static char *concat_given_paths(client_t *client, char *str, char *path)
{
    char *concated = NULL;

    if (str[0] == SLASH) {
        concated = build_path(path, &str[1], true);
    } else {
        concated = build_path(client->cwd, str, true);
    }
    if (!concated || !is_dir(concated)) {
        SAFE_WRITE(client->socket.fd, _550);
        return NULL;
    }
    return concated;
}

void cwd(client_t *client, char **args, char *path)
{
    char *concated = NULL;

    if (!CLIENT_OK(client) || !args || !args[1] || !path) {
        return;
    }
    concated = concat_given_paths(client, args[1], path);
    if (concated) {
        if (strncmp(path, concated, strlen(path)) == MATCH) {
            free(client->cwd);
            client->cwd = concated;
        } else {
            client->cwd = strdup(path);
        }
        SAFE_WRITE(client->socket.fd, _250);
    }
}
