##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME 			= 	myftp

PATH_SRC		=	./src
PATH_COMMAND	=	$(PATH_SRC)/commands
PATH_DATA		=	$(PATH_SRC)/data
PATH_NETWORK	=	$(PATH_SRC)/network
PATH_UTILS		=   $(PATH_SRC)/utils

SRC             =  	$(PATH_SRC)/destroy.c \
					$(PATH_SRC)/main.c \
					$(PATH_SRC)/runner.c \
					$(PATH_SRC)/signal.c

SRC_COMMANDS    =   $(PATH_COMMAND)/cdup.c \
                    $(PATH_COMMAND)/command_manager.c \
                    $(PATH_COMMAND)/cwd.c \
                    $(PATH_COMMAND)/dele.c \
                    $(PATH_COMMAND)/help.c \
                    $(PATH_COMMAND)/list.c \
                    $(PATH_COMMAND)/noop.c \
                    $(PATH_COMMAND)/pasv.c \
                    $(PATH_COMMAND)/pass.c \
                    $(PATH_COMMAND)/port.c \
                    $(PATH_COMMAND)/pwd.c \
                    $(PATH_COMMAND)/quit.c \
                    $(PATH_COMMAND)/retr.c \
                    $(PATH_COMMAND)/stor.c \
                    $(PATH_COMMAND)/user.c

SRC_DATA		= 	$(PATH_DATA)/client/alloc.c \
					$(PATH_DATA)/client/manage.c \
					$(PATH_DATA)/channel.c \
					$(PATH_DATA)/input.c \
					$(PATH_DATA)/manager.c

SRC_NETWORK		= 	$(PATH_NETWORK)/network_manager.c \
					$(PATH_NETWORK)/network_init.c \

SRC_UTILS       =  	$(PATH_UTILS)/get_args.c \
					$(PATH_UTILS)/lib.c \
					$(PATH_UTILS)/print.c

ALL_SRCS 		=	$(SRC) \
					$(SRC_COMMANDS) \
					$(SRC_DATA) \
					$(SRC_NETWORK) \
					$(SRC_UTILS)

OBJ 			=	$(ALL_SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-W -Wall -Wextra -Werror

INCLUDES		=	-I./include

$(NAME): $(OBJ)
	$(CC) $(INCLUDES) $(OBJ) -o $(NAME) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
