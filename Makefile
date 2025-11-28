##
## EPITECH PROJECT, 2024
## Day 9
## File description:
## Makefile
##

CC = gcc

CPP = g++

LIB = ar rc

SRC	=	src/Grid.cpp 			\
		src/main.cpp 			\
		src/AliveCell.cpp 		\
		src/DeadCell.cpp 		\
		src/Game.cpp 			\
		src/ConsoleMode.cpp 	\
		src/GUI.cpp				\
		src/ObstacleCell.cpp	\
		src/GameRule.cpp		\
		src/Background.cpp		\
		src/Assets.cpp			\
		src/GameRuleSet.cpp		\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	jeudelavie

CXXFLAGS =	-std=c++20 -Wall -Wextra -Werror -Iinclude

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CPP) $(OBJ) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system

clean:
		rm -f $(OBJ)
		rm -f *~
		rm -f "#*#"

fclean:		clean
	rm -f $(NAME)
re:		fclean all

run:	all
		./$(NAME)
