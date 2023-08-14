CC=gcc
GCC_FLAGS=-Wall -Werror -Wextra -pedantic -std=gnu89 -g
VAL_FLAGS=--track-origins=yes --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 -s
SRC= *.c
NAME=shell

all: compile run remove

compile:
	@$(CC) $(GCC_FLAGS) $(SRC) -o $(NAME)

run:
	@valgrind $(VAL_FLAGS) ./$(NAME)

remove:
	@rm $(NAME)