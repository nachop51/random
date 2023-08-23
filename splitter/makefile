CC=gcc
GCC_FLAGS=-Wall -Werror -Wextra -pedantic -std=gnu99 -g
VAL_FLAGS=--track-origins=yes --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 -s
SRC= *.c
NAME=splitter
ARGS=args.txt

all: build valgrind remove

build:
	@$(CC) $(GCC_FLAGS) $(SRC) -o $(NAME)

valgrind: build
	@valgrind $(VAL_FLAGS) ./$(NAME) $(ARGS)

run: build
	@./$(NAME) $(ARGS)

remove:
	@rm $(NAME)
