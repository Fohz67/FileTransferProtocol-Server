/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** quit.c
*/

#include "my_command_type.h"
#include "consts/my_messages.h"

void quit(client_t *client, char **args, char *path)
{
    (void)args;
    (void)path;
    if (CLIENT_OK(client)) {
        SAFE_WRITE(client->socket.fd, _221);
        remove_specific_client(client);
    }
}
