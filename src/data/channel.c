/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** client.c
*/

#include "my_ftp.h"
#include "network/my_server.h"
#include "network/my_client.h"

static int login_active(client_t *client)
{
    int fd = init_sockopt();
    struct sockaddr *adr = (struct sockaddr *)&client->channel.socket.address;

    if (fd == FAIL) {
        return ERROR;
    }
    if (connect(fd, adr, sizeof(struct sockaddr_in)) == FAIL) {
        return ERROR;
    }
    client->channel.fd = fd;
    return SUCCESS;
}

static int login_passive(client_t *client)
{
    client_t *new_client = NULL;

    new_client = alloc_new_client(&client->channel.socket, EMPTY, false);
    if (new_client) {
        client->channel.fd = new_client->socket.fd;
        free(new_client->cwd);
        free(new_client);
        return SUCCESS;
    }
    return ERROR;
}

int login_channel(client_t *client)
{
    if (client->channel.fd != SUCCESS) {
        return ERROR;
    }
    if (client->channel.status == ACTIVE) {
        return login_active(client);
    }
    if (client->channel.status == PASSIVE) {
        return login_passive(client);
    }
    return SUCCESS;
}
