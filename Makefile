##
## EPITECH PROJECT, 2019
## myarpspoof
## File description:
## Makefile
##

NAME_CLIENT	=	zappy_ai

NAME_SRV	=	zappy_server

CFLAGS		=	-I./include/ -g3 -D_GNU_SOURCE=1

SRC_SRV		=	main.c							\
				./src/server/pars_arg_serv.c	\
				./src/server/utils.c			\
				./src/server/map.c				\
				./src/server/send_map.c			\
				./src/server/move_cmd.c			\
				./src/server/info_cmd.c			\
				./src/server/server.c			\
				./src/server/multiplexing.c		\
				./src/server/message.c			\
				./src/server/get_user.c			\
				./src/server/list.c				\
				./src/server/items_cmd.c		\
				./src/server/exec_cmd.c			\
				./src/server/get_fd.c			\
				./src/server/read_cmds.c		\
				./src/server/auth.c				\
				./src/server/stats_cmd.c
OBJ_SRV		=	$(SRC_SRV:.c=.o)

all:			$(NAME_SRV)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) $(OBJ_SRV) -o $(NAME_SRV) $(LDFLAGS)

zappy_ai:
	cp src/client/client.py $(NAME_CLIENT)

clean:
	$(RM) $(OBJ_SRV)

fclean: clean
	$(RM) $(NAME_SRV) $(NAME_CLIENT)

re: fclean all
