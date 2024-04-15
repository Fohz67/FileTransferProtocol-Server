/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** list.c
*/

#include "my_command_type.h"
#include "my_utils.h"

static const char P_OPEN_FLAG[] = "r";
static const char LS_CMD[] = "/bin/ls -l ";
static const char __150[] =
"150 File status okay; about to open data connection.\r\n";

static void ls_syscall(client_t *client, char *path)
{
    FILE *file = NULL;
    char buffer[READ_SIZE + 1] = {END_STR};
    char *cmd = NULL;

    cmd = concat_strings(LS_CMD, path);
    file = popen(cmd, P_OPEN_FLAG);
    free(cmd);
    if (file) {
        while (fgets(buffer, READ_SIZE, file)) {
            write(client->channel.fd, buffer, strlen(buffer));
            memset(buffer, END_STR, READ_SIZE);
        }
        SAFE_WRITE(client->socket.fd, _226);
        pclose(file);
    } else {
        SAFE_WRITE(client->socket.fd, _426);
    }
}

static void fork_it(client_t *client, char *path)
{
    pid_t pid;

    if (login_channel(client) == ERROR) {
        SAFE_WRITE(client->socket.fd, _425);
        free(path);
        return;
    }
    pid = fork();
    if (pid == FAIL) {
        SAFE_WRITE(client->socket.fd, _425);
        return;
    }
    if (pid == SUCCESS) {
        SAFE_WRITE(client->socket.fd, __150);
        ls_syscall(client, path);
        free(path);
        destroy_all(get_server_everywhere(NULL));
        exit(EXIT_SUCCESS);
    }
}

static char *get_fp(client_t *client, char *str, char *path)
{
    char *fp = NULL;

    if (str[0] == SLASH) {
        fp = build_path(path, &str[1], false);
    } else {
        fp = build_path(client->cwd, str, false);
    }
    if (!fp) {
        SAFE_WRITE(client->socket.fd, _550);
        return NULL;
    }
    return fp;
}

void compute_with_fp(client_t *client, char **args, char *path)
{
    char *str = NULL;

    if (!args[1]) {
        str = strdup(client->cwd);
    } else {
        str = get_fp(client, args[1], path);
    }
    if (str) {
        fork_it(client, path);
        destroy_channel(client);
    }
}

void list(client_t *client, char **args, char *path)
{
    if (!CLIENT_OK(client) || !args || !path) {
        return;
    }
    if (client->channel.status == NONE) {
        SAFE_WRITE(client->socket.fd, _425);
        return;
    }
    compute_with_fp(client, args, path);
}
