##
## EPITECH PROJECT, 2019
## myarpspoof
## File description:
## Makefile
##

NAME_CLIENT	=	zappy_ai

NAME_SRV	=	zappy_server

CFLAGS		=	-I./includes/

SRC_CLIENT	=	./src/client/client.c

SRC_SRV		=	./src/server/server.c

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

OBJ_SRV		=	$(SRC_SRV:.c=.o)

all:			$(NAME_CLIENT) $(NAME_SRV)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(SRC_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) $(OBJ_SRV) -o $(NAME_SRV) $(LDFLAGS)

clean:
	$(RM) $(OBJ_SRV) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_SRV) $(NAME_CLIENT)

re: fclean all