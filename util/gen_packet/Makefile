NAME=gen_fwall
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -fstack-protector-all -pie

BUILD_DIR = ../../build

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
OTHER_SRC = ../../src/convert.c
OTHER_OBJ = $(patsubst %.c, %.o, $(OTHER_SRC))

TEST_FLAGS = -fsanitize=address -fsanitize=leak -g -lcheck

STYLE=GNU


all: clean $(NAME)


$(NAME): $(OBJ) $(OTHER_OBJ)
	$(CC) $^ $(CFLAGS) -o $@
	strip $(NAME)
	mv $@ $(BUILD_DIR)

$(OTHER_OBJ): 
	$(CC) $^ $(CFLAGS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(NAME)
	rm -rf $(BUILD_DIR)/$(NAME)

style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
