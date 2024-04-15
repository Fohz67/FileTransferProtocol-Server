/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** retr.c
*/

#include "my_command_type.h"
#include <sys/stat.h>
#include <fcntl.h>

static const char __150[] =
"150 File status okay; about to open data connection.\r\n";

static void send_file(client_t *client, int fd)
{
    ssize_t read_fd;
    char buffer[READ_SIZE + 1] = {END_STR};

    for (;;) {
        read_fd = read(fd, buffer, READ_SIZE);
        if (read_fd <= SUCCESS) {
            break;
        }
        if (write(client->channel.fd, buffer, read_fd) == FAIL) {
            SAFE_WRITE(client->socket.fd, _426);
            return;
        }
        memset(&buffer, END_STR, READ_SIZE);
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
        send_file(client, fd);
        close(fd);
        destroy_all(get_server_everywhere(NULL));
        exit(EXIT_SUCCESS);
    }
}

static int read_fd(client_t *client, char *str, char *path)
{
    struct stat st;
    char *fp = NULL;
    int fd;

    if (str[0] == SLASH) {
        fp = build_path(path, &str[1], false);
    } else {
        fp = build_path(client->cwd, str, false);
    }
    fd = fp ? open(fp, O_RDONLY) : FAIL;
    if (!fp || fd == FAIL) {
        SAFE_WRITE(client->socket.fd, _550);
        return FAIL;
    }
    if (fstat(fd, &st) == FAIL || !S_ISREG(st.st_mode)) {
        SAFE_WRITE(client->socket.fd, _550);
        return FAIL;
    }
    return fd;
}

static void compute_with_fd(client_t *client, char *str, char *path)
{
    int fd = read_fd(client, str, path);

    if (fd != FAIL) {
        fork_it(client, fd);
        close(fd);
        destroy_channel(client);
    }
}

void retr(client_t *client, char **args, char *path)
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
