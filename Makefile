NAME=firewall_prototype
CC = gcc
CFLAGS = -Wall -Werror -Wextra

BUILD_DIR = build/

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

GCOV_FLAGS = --coverage
TEST_FLAGS = 
TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

STYLE=GNU


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $^ -o $@


.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(TEST_OBJ) $(NAME)


style:
	clang-format -style=$(STYLE) -i *.c
