/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** runner.c
*/

#include "my_ftp.h"
#include "my_signal.h"
#include "network/my_server.h"
#include "network/my_client.h"

static int loop(server_t *server)
{
    get_server_everywhere(server);
    if (exit_signal() == FAIL) {
        return FAIL;
    }
    while (*get_signal_flag_ptr() == 0) {
        manage_file_descriptors(server);
        if (manage_select(server) == FAIL) {
            break;
        }
        check_each_fds(server);
    }
    destroy_all(server);
    return SUCCESS;
}

int runner(const in_port_t port, char *path, server_t *server)
{
    server->path = path;
    server->port = port;
    if (create_socket(server) == FAIL ||
        pre_alloc_clients(server) == FAIL ||
        loop(server) == FAIL) {
        return FAIL;
    }
    return SUCCESS;
}
