/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** manage.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "network/my_server.h"
#include "network/my_client.h"

static const char REACHED_MAX[] = "Server reached max clients.";

void remove_specific_client(client_t *client)
{
    size_t index = 0;
    server_t *server = get_server_everywhere(NULL);
    size_t size = array_length(server->clients);

    destroy_specific_client(client);
    for (; index < size; index++) {
        if (server->clients[index] == client) {
            server->clients[index] = NULL;
            break;
        }
    }
    for (; index < size; index++) {
        server->clients[index] = server->clients[index + 1];
        server->clients[index + 1] = NULL;
    }
}

void check_each_fds(server_t *server)
{
    for (size_t index = 0; index < FD_SETSIZE; index++) {
        if (FD_ISSET(index, &server->fds)) {
            check_fds(server, index);
        }
    }
}

void add_new_client(server_t *server)
{
    client_t *new_client = NULL;
    size_t size;

    new_client = alloc_new_client(server->socket, server->path, true);
    size = array_length(server->clients);
    if (!new_client) {
        return;
    }
    if (size >= FD_SETSIZE) {
        output_error(REACHED_MAX);
        close(new_client->socket.fd);
        free(new_client);
        return;
    }
    server->clients[size] = new_client;
}
