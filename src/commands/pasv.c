/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** pasv.c
*/

#include "my_command_type.h"
#include <arpa/inet.h>

static const char PRINT_CHANNEL[] = "%d.%d.%d.%d";
static const int DIVIDER = 256;

static void create_channel(client_t *client, int socket)
{
    char *ip = inet_ntoa(client->channel.socket.address.sin_addr);
    int n[4] = {0};
    int port;
    int pd;
    int pm;

    sscanf(ip, PRINT_CHANNEL, &n[0], &n[1], &n[2], &n[3]);
    port = ntohs(client->channel.socket.address.sin_port);
    pd = port / DIVIDER;
    pm = port % DIVIDER;
    dprintf(client->socket.fd, _227, n[0], n[1], n[2], n[3], pd, pm);
    client->channel.status = PASSIVE;
    client->channel.socket.fd = socket;
}

void pasv(client_t *client, char **args, char *path)
{
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr *adr;
    int socket;

    (void)args;
    (void)path;
    if (!CLIENT_OK(client)) {
        return;
    }
    destroy_channel(client);
    socket = setup_server_socket(init_sockopt(), 0);
    if (socket != FAIL) {
        adr = (struct sockaddr *)&client->channel.socket.address;
        getsockname(socket, adr, &len);
        create_channel(client, socket);
    } else {
        SAFE_WRITE(client->socket.fd, _425);
    }
}
