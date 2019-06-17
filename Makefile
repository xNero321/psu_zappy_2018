##
## EPITECH PROJECT, 2019
## myarpspoof
## File description:
## Makefile
##

NAME_CLIENT	=	zappy_ai

NAME_SRV	=	zappy_server

CFLAGS		=	-I./includes/

SRC_SRV		=	./src/server/server.c
				./src/server/pars_arg_serv.clean.c
				./src/server/utils.c
				
OBJ_SRV		=	$(SRC_SRV:.c=.o)

all:			$(NAME_CLIENT) $(NAME_SRV)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) $(OBJ_SRV) -o $(NAME_SRV) $(LDFLAGS)

clean:
	$(RM) $(OBJ_SRV)

fclean: clean
	$(RM) $(NAME_SRV)

re: fclean all