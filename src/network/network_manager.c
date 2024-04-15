/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** network_manager.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "network/my_server.h"
#include "network/my_client.h"
#include <errno.h>

static const char SELECT_FAILED[] = "Select failed.";
static const char TIMED_OUT[] = "Timed out.";

server_t *get_server_everywhere(server_t *server)
{
    static server_t *stored = NULL;

    if (server) {
        stored = server;
    }
    return stored;
}

int manage_select(server_t *server)
{
    int result = select(FD_SETSIZE, &server->fds, NULL, NULL, NULL);

    if (result < 0) {
        if (errno == EINTR) {
            return FAIL;
        }
        return output_error(SELECT_FAILED);
    }
    if (result == 0) {
        return output_error(TIMED_OUT);
    }
    if (FD_ISSET(server->socket->fd, &server->fds)) {
        add_new_client(server);
    }
    return SUCCESS;
}

static void ensure_passive_mode_to_set(client_t *client, server_t *server)
{
    bool verified =
        client->channel.status == PASSIVE &&
        client->channel.socket.fd != SUCCESS &&
        client->channel.fd == SUCCESS;

    FD_SET(client->socket.fd, &server->fds);
    if (verified) {
        FD_SET(client->channel.socket.fd, &server->fds);
    }
}

void manage_file_descriptors(server_t *server)
{
    FD_ZERO(&server->fds);
    FD_SET(server->socket->fd, &server->fds);
    for (size_t index = 0; server->clients[index]; index++) {
        ensure_passive_mode_to_set(server->clients[index], server);
    }
}
