/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** stor.c
*/

#include "my_command_type.h"
#include "my_utils.h"
#include <fcntl.h>

static const char PATH_HERE[] = "./";
static const char __150[] =
"150 File status okay; about to open data connection.\r\n";

static void get_file(client_t *client, int fd)
{
    ssize_t read_channel;
    char buffer[READ_SIZE + 1] = {END_STR};

    for (;;) {
        read_channel = read(client->channel.fd, buffer, READ_SIZE);
        if (read_channel <= 0) {
            break;
        }
        if (write(fd, buffer, read_channel) == FAIL) {
            SAFE_WRITE(client->socket.fd, _426);
            return;
        }
        memset(buffer, END_STR, READ_SIZE);
    }
    SAFE_WRITE(client->socket.fd, _226);
}

static void fork_it(client_t *client, int fd)
{
    pid_t pid;

    if (login_channel(client) == ERROR) {
        SAFE_WRITE(client->socket.fd, _425);
        return;
    }
    pid = fork();
    if (pid == FAIL) {
        SAFE_WRITE(client->socket.fd, _425);
        return;
    }
    if (pid == SUCCESS) {
        SAFE_WRITE(client->socket.fd, __150);
        get_file(client, fd);
        close(fd);
        destroy_all(get_server_everywhere(NULL));
        exit(EXIT_SUCCESS);
    }
}

static char *get_fp(client_t *client, char *str, char *path)
{
    char *fp = NULL;

    if (str[0] == SLASH) {
        fp = concat_strings(path, &str[1]);
        return fp;
    }
    fp = str;
    while (strncmp(fp, PATH_HERE, 2) == SUCCESS) {
        fp += 2;
    }
    fp = concat_strings(client->cwd, fp);
    return fp;
}

static int write_fd(client_t *client, char *str, char *path)
{
    char *fp = get_fp(client, str, path);
    int fd = 0;

    if (fp) {
        fd = open(fp, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    }
    if (!fp || fd == FAIL) {
        SAFE_WRITE(client->socket.fd, _550);
        return FAIL;
    }
    free(fp);
    return fd;
}

static void compute_with_fd(client_t *client, char *str, char *path)
{
    int fd = write_fd(client, str, path);

    if (fd != FAIL) {
        fork_it(client, fd);
        close(fd);
        destroy_channel(client);
    }
}

void stor(client_t *client, char **args, char *path)
{
    if (!CLIENT_OK(client) || !args || !path) {
        return;
    }
    if (client->channel.status == NONE) {
        SAFE_WRITE(client->socket.fd, _425);
        return;
    }
    if (!args[1]) {
        SAFE_WRITE(client->socket.fd, _550);
        return;
    }
    compute_with_fd(client, args[1], path);
}
