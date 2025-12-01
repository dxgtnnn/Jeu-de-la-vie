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
		src/Music.cpp			\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	jeudelavie

CXXFLAGS =	-std=c++20 -Wall -Wextra -Werror -Iinclude

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CPP) $(OBJ) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# ============================================ #
#               CRITERION TESTS                #
# ============================================ #


CRIT_SRC = 	tests/criterion_grid.cpp \
	tests/criterion_grid_more.cpp \
	tests/criterion_cells.cpp \
	tests/criterion_cells_more.cpp \
	tests/criterion_rules.cpp \
	tests/criterion_rules_more.cpp \
		src/Grid.cpp \
		src/AliveCell.cpp \
		src/DeadCell.cpp \
		src/ObstacleCell.cpp \
		src/GameRule.cpp \
		src/GameRuleSet.cpp \
		src/Background.cpp \
		src/Assets.cpp \
		src/Music.cpp

CRIT_OBJ = $(CRIT_SRC:.cpp=.o)
CRIT_NAME = criterion_unit_tests

criterion_tests: CXXFLAGS += -Iinclude -std=c++17 -Wall -Wextra
criterion_tests: $(CRIT_OBJ)
	$(CPP) $(CRIT_OBJ) -o $(CRIT_NAME) -lcriterion -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./$(CRIT_NAME)

clean_tests:
	rm -f tests/*.o
	rm $(CRIT_NAME)

clean:
		rm -f $(OBJ)
		rm -f *~
		rm -f "#*#"

fclean:		clean
	rm -f $(NAME)
	rm -rf *_out
re:		fclean all

run:	all
		./$(NAME)
