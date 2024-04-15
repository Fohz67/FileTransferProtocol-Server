/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** clients.new_client
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "consts/my_messages.h"
#include "network/my_server.h"
#include "network/my_client.h"
#include "network/my_commands.h"

static void manage_args(client_t *client, char *buffer,
    char *path)
{
    char **args = NULL;

    args = transform_to_array(buffer);
    if (array_length(args) > 0) {
        command_execute(client, args, path);
        for (size_t index = 0; args[index]; index++) {
            free(args[index]);
        }
        free(args);
    } else {
        SAFE_WRITE(client->socket.fd, client->is_logged ? _500 : _530);
    }
}

static void accept_fds(client_t *client)
{
    client_t *new_client = NULL;

    new_client = alloc_new_client(&client->channel.socket, EMPTY, false);
    if (new_client) {
        client->channel.fd = new_client->socket.fd;
        free(new_client->cwd);
        free(new_client);
    }
}

static void get_command(client_t *client, char *path)
{
    char *buffer = input_client(client);

    if (!buffer) {
        remove_specific_client(client);
        return;
    }
    if (strcmp(buffer, EMPTY) == MATCH) {
        free(buffer);
        return;
    }
    manage_args(client, buffer, path);
    free(buffer);
}

void check_fds(server_t *server, int fd)
{
    for (size_t index = 0; server->clients[index]; index++) {
        if (!server->clients[index]) {
            continue;
        }
        if (server->clients[index]->socket.fd == fd) {
            return get_command(server->clients[index], server->path);
        }
        if (server->clients[index]->channel.socket.fd == fd) {
            return accept_fds(server->clients[index]);
        }
    }
}
