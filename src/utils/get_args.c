/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** get_args.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include <stdint.h>

static const char PATH_INVALID[] = "Invalid path given.";
static const char PATH_NOT_DIR[] = "Path given is not a directory.";
static const char PORT_CONVERSION[] = "Can't convert the port given.";
static const char PORT_LIMIT[] = "Port given is too big.";

static char *transform_path(char *path, bool is_dir)
{
    char *tmp = NULL;
    size_t length;

    if (!is_dir) {
        return path;
    }
    length = strlen(path);
    if (path[length - 1] != SLASH) {
        tmp = realloc(path, length + 2);
        if (!tmp) {
            free(path);
            return NULL;
        }
        path = tmp;
        path[length] = SLASH;
        path[length + 1] = END_STR;
    }
    return path;
}

char *build_path(const char *cwd, const char *filepath, bool is_dir)
{
    char *new = NULL;
    char *path = NULL;

    new = concat_strings(cwd, filepath);
    if (!new) {
        return NULL;
    }
    path = realpath(new, NULL);
    free(new);
    if (!path) {
        return NULL;
    }
    return transform_path(path, is_dir);
}

in_port_t get_port(const char **av)
{
    char *endptr = NULL;
    long conv;
    in_port_t port;

    conv = strtol(av[1], &endptr, 10);
    if (endptr == av[1]) {
        output_error(PORT_CONVERSION);
        exit(ERROR);
    }
    if (conv < 0 || conv > UINT16_MAX) {
        output_error(PORT_LIMIT);
        exit(ERROR);
    }
    port = (in_port_t)conv;
    return port;
}

char *get_path(const char **av)
{
    char *path = NULL;

    path = build_path(av[2], EMPTY, true);
    if (!path) {
        output_error(PATH_INVALID);
        exit(ERROR);
    }
    if (!is_dir(path)) {
        output_error(PATH_NOT_DIR);
        exit(ERROR);
    }
    return path;
}
