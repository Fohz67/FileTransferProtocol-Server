/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** command_manager.c
*/

#include "my_command_type.h"
#include "my_utils.h"

static const command_t command[] = {
    {"CDUP", &cdup, 1, true},
    {"CWD", &cwd, 2, true},
    {"DELE", &dele, 2, true},
    {"HELP", &help, 1, true},
    {"LIST", &list, 1, true},
    {"NOOP", &noop, 1, true},
    {"PASV", &pasv, 1, true},
    {"PASS", &pass, 1, false},
    {"PORT", &port, 2, true},
    {"PWD", &pwd, 1, true},
    {"QUIT", &quit, 1, false},
    {"RETR", &retr, 1, true},
    {"STOR", &stor, 1, true},
    {"USER", &user, 1, false},
    {NULL, NULL, 0, false}
};

static bool exist_cmd(command_t command, char **args)
{
    return (strcmp(command.name, args[0]) == SUCCESS);
}

static bool unrestricted_cmd(client_t *client, command_t command,
    int array_len)
{
    return ((array_len >= command.args || command.args == FAIL) &&
        (command.is_logged == false ||
        (command.is_logged == true && client->is_logged == true)));
}

static bool restricted_cmd(client_t *client, command_t command)
{
    return (command.is_logged == true && client->is_logged == false);
}

static bool invalid_cmd(command_t command, int array_len)
{
    return (array_len < command.args);
}

void command_execute(client_t *client, char **args, char *path)
{
    size_t array_len = array_length(args);

    for (size_t index = 0; command[index].name; index++) {
        if (!exist_cmd(command[index], args)) {
            continue;
        }
        if (unrestricted_cmd(client, command[index], (int)array_len)) {
            return command[index].ptr(client, args, path);
        }
        if (restricted_cmd(client, command[index])) {
            SAFE_WRITE(client->socket.fd, _530);
            return;
        }
        if (invalid_cmd(command[index], (int)array_len)) {
            SAFE_WRITE(client->socket.fd, _550);
            return;
        }
    }
    SAFE_WRITE(client->socket.fd, client->is_logged ? _500 : _530);
}
