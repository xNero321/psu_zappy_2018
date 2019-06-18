##
## EPITECH PROJECT, 2019
## myarpspoof
## File description:
## Makefile
##

NAME_CLIENT	=	zappy_ai

NAME_SRV	=	zappy_server

CFLAGS		=	-I./include/

SRC_SRV		=	main.c							\
				./src/server/pars_arg_serv.c	\
				./src/server/utils.c			\
				./src/server/map.c

OBJ_SRV		=	$(SRC_SRV:.c=.o)

all:			$(NAME_SRV)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) $(OBJ_SRV) -o $(NAME_SRV) $(LDFLAGS)

clean:
	$(RM) $(OBJ_SRV)

fclean: clean
	$(RM) $(NAME_SRV)

re: fclean all