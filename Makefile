NAME=fwall
CC = gcc
CFLAGS = -Wall -Wextra -Werror

BUILD_DIR = build/

UTIL_NAME = gen_$(NAME)
UTIL_PATH = util/gen_packet

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

GCOV_FLAGS = --coverage
TEST_FLAGS = -fsanitize=address -fsanitize=leak -g -lcheck
TEST_SRC = test/*.c src/convert.c src/firewall_db.c src/rule.c
TEST_EXEC = $(NAME)_test

STYLE=GNU


all: clean $(NAME) $(UTIL_NAME)


$(NAME): $(OBJ)
	$(CC) $^ $(TEST_FLAGS) -o $@ -lasan -lubsan
	mv $@ $(BUILD_DIR)

$(UTIL_NAME): $(OBJ)
	make -C $(UTIL_PATH)


test: clean $(TEST_SRC)
	$(CC) $(TEST_SRC) $(TEST_FLAGS) -o $(TEST_EXEC)


debug: clean
	$(CC) -g $(CFLAGS) $(SRC) -o debug

gcov: clean 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o $(TEST_EXEC)_gcov.info -c -d .
	genhtml -o report $(TEST_EXEC)_gcov.info
	open report/index.html


.c.o:
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(NAME) debug
	rm -rf $(UTIL_OBJ) $(UTIL_NAME)
	rm -rf $(TEST_EXEC) a.out
	rm -rf *.info *.gcda *.gcno
	rm -rf report/ build/*
	make -C $(UTIL_PATH) clean


style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
	make -C $(UTIL_PATH)
