/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** my_commands.h
*/

#ifndef MY_COMMANDS_H
    #define MY_COMMANDS_H

    #include <stdbool.h>

    #define ANONYMOUS_NAME "Anonymous"
    #define CLIENT_OK(client) ((client) && (client)->socket.fd >= 0)
    #define SAFE_WRITE(fd, msg) write((fd), (msg), strlen(msg))

// Anonymous declarations
typedef struct client_s client_t;

// Command structure
typedef struct command_s {
    char *name;
    void (*ptr)(client_t *, char **, char *);
    int args;
    bool is_logged;
} command_t;

// All commands
void command_execute(client_t *, char **, char *);
void cdup(client_t *, char **, char *);
void dele(client_t *, char **, char *);
void help(client_t *, char **, char *);
void noop(client_t *, char **, char *);
void pass(client_t *, char **, char *);
void pwd(client_t *, char **, char *);
void quit(client_t *, char **, char *);
void user(client_t *, char **, char *);
void stor(client_t *, char **, char *);
void retr(client_t *, char **, char *);
void pasv(client_t *, char **, char *);
void cwd(client_t *, char **, char *);
void port(client_t *, char **, char *);
void list(client_t *, char **, char *);

#endif
