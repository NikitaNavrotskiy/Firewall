NAME=firewall_prototype
CC = gcc
CFLAGS = -Wall -Wextra #-Werror

BUILD_DIR = build/

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

GCOV_FLAGS = --coverage
TEST_FLAGS = -fsanitize=address -fsanitize=leak
TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

STYLE=GNU


all: clean $(NAME)


$(NAME): $(OBJ)
	$(CC) $^ $(TEST_FLAGS) -o $@ -lasan -lubsan


debug: clean
	$(CC) -g $(CFLAGS) $(SRC) -o debug  


.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(TEST_OBJ) $(NAME) debug


style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
