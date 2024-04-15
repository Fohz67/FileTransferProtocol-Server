/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** input.c
*/

#include "my_ftp.h"
#include "my_utils.h"
#include "network/my_server.h"
#include "network/my_client.h"

static void concat_buffer_input(client_t *client, char *buffer,
    int read_socket)
{
    size_t increase_capacity = read_socket + 1;
    size_t new_size = str_length(client->buffer) + increase_capacity;
    char *tmp = realloc(client->buffer, new_size);

    if (!client->buffer) {
        memset(tmp, END_STR, increase_capacity);
    }
    strcat(tmp, buffer);
    client->buffer = tmp;
}

char **transform_to_array(char *buffer)
{
    char **array = NULL;
    char *token = NULL;

    token = strtok(buffer, SPACE);
    for (size_t index = 0; token; index++) {
        array = realloc(array, sizeof(char *) * (array_length(array) + 2));
        array[index] = strdup(token);
        array[index + 1] = NULL;
        token = strtok(NULL, SPACE);
    }
    return array;
}

static char *transform_to_not_null(client_t *client)
{
    char *tmp = NULL;

    tmp = strchr(client->buffer, '\n');
    if (!tmp) {
        return strdup(EMPTY);
    }
    *tmp = END_STR;
    tmp = strchr(client->buffer, '\r');
    if (tmp) {
        *tmp = END_STR;
    }
    tmp = client->buffer;
    client->buffer = NULL;
    return tmp;
}

char *input_client(client_t *client)
{
    size_t read_socket;
    char buffer[READ_SIZE + 1] = {END_STR};
    char *tmp = NULL;

    read_socket = read(client->socket.fd, buffer, READ_SIZE);
    if (read_socket <= SUCCESS) {
        tmp = client->buffer;
        client->buffer = NULL;
        return tmp;
    }
    concat_buffer_input(client, buffer, read_socket);
    return transform_to_not_null(client);
}
