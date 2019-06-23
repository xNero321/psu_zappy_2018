##
## EPITECH PROJECT, 2019
## gui
## File description:
## Makefile
##

NAME	=	zappy_gui

CC	=	g++

SRC	=	src/main.cpp			\
		src/Core.cpp			\
		src/NetworkManager.cpp			\
		src/Map.cpp			\
		src/MapCell.cpp			\
		src/Item.cpp \

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS  =	-I./include/ -W -Wall -Wextra -std=c++14

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) -lsfml-window -lsfml-graphics -lsfml-system $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	re all clean fclean