/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** clients.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "consts/my_messages.h"
#include "network/my_server.h"
#include "network/my_client.h"

static const char CLIENT_ALLOC[] = "Can't alloc clients properly.";
static const char ACCEPT_FAILED[] = "Accept failed.";
static const char WRITE_FAILED[] = "Write failed.";

client_t *alloc_new_client(socket_t *socket, char *path, bool auth)
{
    int fd;
    struct sockaddr_in address = {0};
    socklen_t socklen = sizeof(address);
    client_t *new_client = malloc(sizeof(client_t));

    if (!new_client) {
        return output_null_error(CLIENT_ALLOC);
    }
    memset(new_client, 0, sizeof(client_t));
    fd = accept(socket->fd, (struct sockaddr*)&address, &socklen);
    if (fd == FAIL) {
        free(new_client);
        return output_null_error(ACCEPT_FAILED);
    }
    if (auth && write(fd, _220, strlen(_220)) == FAIL) {
        return output_null_error(WRITE_FAILED);
    }
    new_client->socket.fd = fd;
    new_client->cwd = strdup(path);
    return new_client;
}

int pre_alloc_clients(server_t *server)
{
    server->clients = malloc(sizeof(client_t *) * (FD_SETSIZE + 1));
    if (!server->clients) {
        return output_error(CLIENT_ALLOC);
    }
    memset(server->clients, 0, sizeof(client_t *) * (FD_SETSIZE + 1));
    return SUCCESS;
}
