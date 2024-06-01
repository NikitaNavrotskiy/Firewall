NAME=gen_fwall
CC = gcc
CFLAGS = -Wall -Wextra -Werror

BUILD_DIR = ../../build

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
OTHER_SRC = ../../src/convert.c
OTHER_OBJ = $(patsubst %.c, %.o, $(OTHER_SRC))

TEST_FLAGS = -fsanitize=address -fsanitize=leak -g -lcheck

STYLE=GNU


all: clean $(NAME)


$(NAME): $(OBJ) $(OTHER_OBJ)
	$(CC) $^ $(TEST_FLAGS) -o $@ -lasan -lubsan
	mv $@ $(BUILD_DIR)

$(OTHER_OBJ): 
	$(CC) $^ $(TEST_FLAGS) -o $@ -lasan -lubsan

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(NAME)
	rm -rf $(BUILD_DIR)/$(NAME)

style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
