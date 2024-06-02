NAME=fwall
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -fstack-protector-all -pie 
DISTRO = $(shell lsb_release -a 2>/dev/null| grep Distributor | cut -d ':' -f2 | tr -d '\t')

BUILD_DIR = build/
DOC_DIR = docs

UTIL_NAME = gen_$(NAME)
UTIL_PATH = util/gen_packet

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

GCOV_FLAGS = --coverage
TEST_FLAGS = -fsanitize=address -fsanitize=leak -g -lcheck
TEST_SRC = test/*.c src/convert.c src/firewall_db.c src/rule.c
TEST_EXEC = $(NAME)_test

MAKE_BUILD_DIR = mkdir -p $(BUILD_DIR)

STYLE=GNU


ifeq ($(DISTRO), Ubuntu)
	TEST_FLAGS += -lm -lsubunit
endif


all: clean $(NAME) $(UTIL_NAME)


$(NAME): $(OBJ)
	$(MAKE_BUILD_DIR)
	$(CC) $^ $(CFLAGS) -o $@
	strip $(NAME)
	mv $@ $(BUILD_DIR)

$(UTIL_NAME): $(OBJ)
	$(MAKE_BUILD_DIR)
	make -C $(UTIL_PATH)


test: clean $(TEST_SRC)
	$(CC) $(TEST_SRC) $(TEST_FLAGS) -o $(TEST_EXEC)
	./$(TEST_EXEC)


debug: clean
	$(CC) -g $(CFLAGS) $(SRC) -o debug

gcov: clean 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o $(TEST_EXEC)_gcov.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report $(TEST_EXEC)_gcov.info --rc lcov_branch_coverage=1
	open report/index.html


.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

doc:
	doxygen
	open $(DOC_DIR)/html/index.html


clean:
	rm -rf $(OBJ) $(NAME) debug
	rm -rf $(UTIL_OBJ) $(UTIL_NAME)
	rm -rf $(TEST_EXEC) a.out
	rm -rf *.info *.gcda *.gcno
	rm -rf report/ $(BUILD_DIR)* $(DOC_DIR)/*
	make -C $(UTIL_PATH) clean


style:
	clang-format -style=$(STYLE) -i $(SRC) src/*.h
	make -C $(UTIL_PATH) style
