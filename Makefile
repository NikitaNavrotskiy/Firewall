NAME=firewall_prototype
CC = gcc
CFLAGS = -Wall -Wextra #-Werror

BUILD_DIR = build/

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

GCOV_FLAGS = --coverage
TEST_FLAGS = -fsanitize=address -fsanitize=leak -g -lcheck
TEST_SRC = test/*.c src/convert.c src/firewall_db.c src/rule.c
TEST_EXEC = $(NAME)_test

STYLE=GNU


all: clean $(NAME)


$(NAME): $(OBJ)
	$(CC) $^ $(TEST_FLAGS) -o $@ -lasan -lubsan

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
	rm -rf $(TEST_EXEC) a.out
	rm -rf *.info *.gcda *.gcno
	rm -rf report/


style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
