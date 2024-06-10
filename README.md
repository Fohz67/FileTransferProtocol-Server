
# my_ftp

## Overview
my_ftp is a File Transfer Protocol (FTP) server implementation as part of the B-NWP-400 network programming project. This server is written in C and facilitates file transfers over a network using TCP sockets. The server handles multiple client connections simultaneously and supports a range of FTP commands compliant with the ```RFC 959```.

## Features
- **Concurrent Client Handling:** Uses `select` for command management and `fork` for data transfer to handle multiple clients.
- **Authentication:** Supports an Anonymous account with an empty password.
- **Data Transfer Modes:** Supports both active and passive data transfer modes.
- **Error Handling:** Proper error messages and exit codes (84 for errors, 0 for success).

## Compilation
Compile the project using the provided Makefile with the following commands:
- `make`: Compiles the source files.
- `make re`: Re-compiles all files.
- `make clean`: Removes object files.
- `make fclean`: Removes object files and binary.

## Usage
```
./myftp port path
```
- `port`: Port number on which the server will listen.
- `path`: Path to the home directory for the Anonymous user.

To test on your computer, please use Telnet with the loopback IP address 127.0.0.1 in another terminal.

## Supported Commands
- USER
- PASS
- CWD
- CDUP
- QUIT
- DELE
- PWD
- PASV
- PORT
- HELP
- NOOP
- RETR
- STOR
- LIST

## Results
- Final result: 100%.
- Final MouliNorme result: 0 info, 0 minor, 0 major.

## Compliance
Follows the mandatory parts of the RFC959 for implementing FTP commands and responses.

## License
This project is under [MIT License](https://github.com/Fohz67/FileTransferProtocol-Server/main/LICENSE).
