/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_server.h
*/

#ifndef MY_SERVER_H
    #define MY_SERVER_H

// Anonymous declarations
typedef struct client_s client_t;
typedef struct socket_s socket_t;

// Socket structure for the server and each client
typedef struct socket_s {
    int fd;
    struct sockaddr_in address;
} socket_t;

// Server structure to init and handle clients
typedef struct server_s {
    fd_set fds;
    in_port_t port;
    char *path;
    client_t **clients;
    socket_t *socket;
} server_t;

// Destroy
void destroy_all(server_t *);

// Manage
void manage_file_descriptors(server_t *);
int manage_select(server_t *);

// Socket
int create_socket(server_t *);
int init_sockopt(void);
int setup_server_socket(int, in_port_t port);

// Utils
server_t *get_server_everywhere(server_t *);

#endif
