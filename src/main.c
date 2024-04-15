/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** main.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "network/my_server.h"

static const int HELP_NB = 2;
static const int MAX_ARGS = 3;
static const char HELP_ARG[] = "-help";
static const char ARGS_ERROR[] = "Only 2 args excepted.";

int main(int ac, const char **av)
{
    struct server_s server = {0};
    char *path = NULL;
    in_port_t port;

    if (ac == HELP_NB && strcmp(av[1], HELP_ARG) == SUCCESS) {
        return output_helper();
    }
    if (ac != MAX_ARGS || !av[2] || !av[1]) {
        return output_error(ARGS_ERROR) + DEFER_FAIL;
    }
    port = get_port(av);
    path = get_path(av);
    return runner(port, path, &server);
}
