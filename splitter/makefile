CC=gcc
GCC_FLAGS=-Wall -Werror -Wextra -pedantic -std=gnu99 -g
VAL_FLAGS=--track-origins=yes --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 -s
SRC= *.c
NAME=splitter
ARGS=$(sh cat args.txt)

all: build

build:
	@$(CC) $(GCC_FLAGS) $(SRC) -o $(NAME)

run:
	@valgrind $(VAL_FLAGS) ./$(NAME) $(ARGS)

remove:
	@rm $(NAME)
