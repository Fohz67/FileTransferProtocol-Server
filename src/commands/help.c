/*
** EPITECH PROJECT, 2024
** my_ftp by Fohz67
** File description:
** help.c
*/

#include "my_command_type.h"

static const char *helps[][2] = {
    {"CDUP", "214 - CHANGE TO PARENT DIRECTORY:\n"
        "This command is a special case of CWD, allowing"
        " the user to move to the parent directory.\r\n"},
    {"CWD", "214 - CHANGE WORKING DIRECTORY:\n"
        "This command allows the user to work with a "
        "different directory for file storage or "
        "retrieval without altering his login or "
        "accounting information.\r\n"},
    {"DELE", "214 - DELETE COMMAND:\n"
        "This command causes the file specified in the "
        "pathname to be deleted at the server site.\r\n"},
    {"HELP", "214 - HELP COMMAND:\n"
        "This command shall cause the server to send "
        "helpful information regarding its "
        "implementation status over the control "
        "connection to the user.\r\n"},
    {"NOOP", "214 - NOOP COMMAND:\n"
        "This command does not affect any parameters or "
        "previously entered commands. It specifies no "
        "action other than that the server send an OK "
        "reply.\r\n"},
    {"PASS", "214 - PASSWORD COMMAND:\n"
        "The argument field is a Telnet string "
        "specifying the user's password. This command "
        "must be immediately preceded by the user name "
        "command.\r\n"},
    {"PASV", "214 - PASSIVE MODE COMMAND:\n"
        "This command requests the server-DTP to "
        "\"listen\" on a data port and to wait for a "
        "connection rather than initiate one.\r\n"},
    {"PORT", "214 - PORT COMMAND:\n"
        "The argument is a HOST-PORT specification for "
        "the data port to be used in data connection.\r\n"},
    {"PWD", "214 - PRINT WORKING DIRECTORY:\n"
        "This command causes the name of the current "
        "working directory to be returned in the "
        "reply.\r\n"},
    {"QUIT", "214 - QUIT COMMAND:\n"
        "This command terminates a USER and if file "
        "transfer is not in progress, the server closes "
        "the control connection.\r\n"},
    {"RETR", "214 - RETRIEVE COMMAND:\n"
        "This command causes the server-DTP to transfer "
        "a copy of the file, specified in the pathname, "
        "to the server- or user-DTP.\r\n"},
    {"STOR", "214 - STORE COMMAND:\n"
        "This command causes the server-DTP to accept "
        "the data transferred via the data connection "
        "and to store the data as a file at the server "
        "site.\r\n"},
    {"USER", "214 - USER COMMAND:\n"
        "The argument field is a Telnet string "
        "identifying the user. This command will "
        "normally be the first command transmitted by "
        "the user.\r\n"},
    {"LIST", "214 - LIST COMMAND:\n"
        "This command causes a list to be sent from the server to the "
        "passive DTP. If the pathname specifies a directory or other "
        "group of files, the server should transfer a list of files "
        "in the specified directory.\r\n"},
    {NULL, NULL}
};

void help(client_t *client, char **args, char *path)
{
    (void)path;
    if (!CLIENT_OK(client) || !args) {
        return;
    }
    if (!args[1]) {
        SAFE_WRITE(client->socket.fd, _214);
        return;
    }
    for (size_t index = 0; helps[index][0]; index++) {
        if (strcmp(helps[index][0], args[1]) == MATCH) {
            SAFE_WRITE(client->socket.fd, helps[index][1]);
            return;
        }
    }
    SAFE_WRITE(client->socket.fd, _214);
}
