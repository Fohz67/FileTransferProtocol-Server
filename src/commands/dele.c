/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** dele.c
*/

#include "my_command_type.h"
#include <sys/stat.h>

static void compute_dele(client_t *client, char **args, char *path)
{
    char *to_delete = NULL;

    if (args[1][0] == SLASH) {
        to_delete = build_path(path, &args[1][1], false);
    } else {
        to_delete = build_path(client->cwd, args[1], false);
    }
    if (to_delete) {
        if (remove(to_delete) == FAIL) {
            SAFE_WRITE(client->socket.fd, _550);
        } else {
            SAFE_WRITE(client->socket.fd, _250);
        }
        free(to_delete);
    } else {
        SAFE_WRITE(client->socket.fd, _550);
    }
}

void dele(client_t *client, char **args, char *path)
{
    struct stat st;

    if (!CLIENT_OK(client) || !args || !args[1] || !path) {
        return;
    }
    if (stat(args[1], &st) == FAIL || !S_ISREG(st.st_mode)) {
        SAFE_WRITE(client->socket.fd, _550);
        return;
    }
    compute_dele(client, args, path);
}
