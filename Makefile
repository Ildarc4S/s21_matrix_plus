CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
LDFLAGS = -lgtest -lgtest_main -lpthread
GCOV_FLAGS = --coverage
TEST_DIR = tests
OBJ_DIR = obj
LIB_NAME = s21_matrix_oop.a

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_NAME = s21_matrix_test
GCOV_FILE = gcov_test

.PHONY: all clean test gcov_report

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^
	ranlib $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(TEST_SRC) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

gcov_report: $(TEST_NAME)
	$(CC) $(FLAGS) $(SRC) $(TEST_SRC) $(LDFLAGS) $(GCOV_FLAGS) -o $(GCOV_FILE)
	./$(GCOV_FILE)
	lcov --capture --directory . --output-file coverage.info --no-external --ignore-errors mismatch
	lcov --remove coverage.info '*/tests/*' '*/usr/*' -o filtered.info --ignore-errors unused
	genhtml filtered.info --output-directory coverage_report

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME) $(TEST_NAME) *.info *.gcda *.gcno $(GCOV_FILE) coverage_report
