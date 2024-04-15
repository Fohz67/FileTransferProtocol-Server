/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** destroy.c
*/

#include "my_ftp.h"
#include "network/my_server.h"
#include "network/my_client.h"

void destroy_channel(client_t *client)
{
    if (client->channel.status != NONE) {
        if (client->channel.fd && client->channel.fd != SUCCESS) {
            close(client->channel.fd);
        }
        if (client->channel.status == PASSIVE && client->channel.socket.fd) {
            close(client->channel.socket.fd);
        }
    }
    memset(&client->channel, 0, sizeof(channel_t));
}

void destroy_specific_client(client_t *client)
{
    if (!client) {
        return;
    }
    if (client->username) {
        free(client->username);
    }
    if (client->password) {
        free(client->password);
    }
    if (client->cwd) {
        free(client->cwd);
    }
    if (client->buffer) {
        free(client->buffer);
    }
    destroy_channel(client);
    close(client->socket.fd);
    free(client);
}

static void destroy_clients(server_t *server)
{
    for (size_t index = 0; server->clients[index]; index++) {
        destroy_specific_client(server->clients[index]);
    }
}

static void close_fds(server_t *server)
{
    for (size_t index = 0; index < FD_SETSIZE; index++) {
        if (FD_ISSET(index, &server->fds)) {
            close(index);
        }
    }
    if (FD_ISSET(server->socket->fd, &server->fds)) {
        FD_ZERO(&server->fds);
    }
}

void destroy_all(server_t *server)
{
    destroy_clients(server);
    close_fds(server);
    if (server->clients) {
        free(server->clients);
    }
    if (server->socket) {
        free(server->socket);
    }
    exit(EXIT_SUCCESS);
}
