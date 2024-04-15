/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** network_init.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "network/my_server.h"

static const char SOCKET_FAILED[] = "Socket creation failed.";
static const char SETSOCKOPT_FAILED[] = "Setsockopt failed.";
static const char BIND_FAILED[] = "Bind failed.";
static const char LISTEN_FAILED[] = "Listen failed.";
static const char FD_ERROR[] = "FD error.";
static const char SOCKET_ERROR[] = "Malloc socket error.";

static struct sockaddr_in set_address(in_port_t port)
{
    struct sockaddr_in address = {0};

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    return address;
}

int setup_server_socket(int fd, in_port_t port)
{
    struct sockaddr_in address = {0};

    if (fd == FAIL) {
        return output_error(FD_ERROR);
    }
    address = set_address(port);
    if (bind(fd, (struct sockaddr *) &address, sizeof(address)) == FAIL) {
        return output_error(BIND_FAILED);
    }
    if (listen(fd, SOMAXCONN) == FAIL) {
        return output_error(LISTEN_FAILED);
    }
    return fd;
}

int init_sockopt(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, SUCCESS);
    int opt = 1;

    if (fd == FAIL) {
        return output_error(SOCKET_FAILED);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == FAIL) {
        return output_error(SETSOCKOPT_FAILED);
    }
    return fd;
}

int create_socket(server_t *server)
{
    int fd = init_sockopt();
    socket_t *socket = NULL;

    if (fd == FAIL || setup_server_socket(fd, server->port) == FAIL) {
        return fd == FAIL ? output_error(FD_ERROR) : FAIL;
    }
    socket = malloc(sizeof(socket_t));
    if (!socket) {
        return output_error(SOCKET_ERROR);
    }
    server->socket = socket;
    socket->fd = fd;
    FD_ZERO(&server->fds);
    FD_SET(socket->fd, &server->fds);
    return SUCCESS;
}
