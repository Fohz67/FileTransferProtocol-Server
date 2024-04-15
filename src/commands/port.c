/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** port.c
*/

#include "my_command_type.h"
#include "my_utils.h"
#include <arpa/inet.h>

static const size_t NEEDED_CHAR = 5;
static const size_t MAX_CHAR = 6;
static const int DIV = 256;
static const char CHAR_TO_COUNT = ',';
static const char P[] = "%d,%d,%d,%d,%d,%d";
static const char PRINT_CHANNEL[] = "%d.%d.%d.%d";
static const char COMMAND_NAME[] = "PORT";

static void create_channel(client_t *client, int c[6])
{
    char ip[16] = {0};

    sprintf(ip, PRINT_CHANNEL, c[0], c[1], c[2], c[3]);
    if (inet_aton(ip, &client->channel.socket.address.sin_addr) != SUCCESS) {
        client->channel.socket.address.sin_family = AF_INET;
        client->channel.socket.address.sin_port = htons((c[4] * DIV) + c[5]);
        dprintf(client->socket.fd, _200, COMMAND_NAME);
        client->channel.status = ACTIVE;
    } else {
        SAFE_WRITE(client->socket.fd, _501);
    }
}

void port(client_t *client, char **args, char *path)
{
    int c[6] = {FAIL};

    (void)path;
    if (!CLIENT_OK(client) || !args || !args[1]) {
        return;
    }
    destroy_channel(client);
    if (count_char(args[1], CHAR_TO_COUNT) != NEEDED_CHAR ||
        sscanf(args[1], P, &c[0], &c[1], &c[2], &c[3], &c[4], &c[5]) == EOF) {
        SAFE_WRITE(client->socket.fd, _501);
        return;
    }
    for (size_t index = 0; index < MAX_CHAR; index++) {
        if (c[index] == FAIL) {
            SAFE_WRITE(client->socket.fd, _501);
            return;
        }
    }
    return create_channel(client, c);
}
