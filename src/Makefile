CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
LDFLAGS = -lcheck -lpthread -lrt -lm -lsubunit --coverage
COVDIR = test_info
GCOVFLAGS = -fprofile-arcs -ftest-coverage
BRANCHES = --rc lcov_branch_coverage=1
SUPPRESS = >> /dev/null 2>&1

TARGET = s21_matrix_oop.a	
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

s21_matrix_oop.a: $(OBJS)
	@ar rcs $@ $^
	@ranlib $@
	@rm $^

main: clean $(TARGET)
	@$(CC) $(CFLAGS) m/main.cpp s21_matrix_oop.a -o m/main
	@m/main

vm: clean $(TARGET)
	@$(CC) $(CFLAGS) m/main.cpp s21_matrix_oop.a -o m/main
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes m/main

test: clean $(TARGET)
	@mkdir -p $(COVDIR)
	@$(CC) $(CFLAGS) tests/*.c *.c $(LDFLAGS) -I. -o $(COVDIR)/test
	@$(COVDIR)/test

valgrind: clean $(TARGET)
	@mkdir -p $(COVDIR)
	@$(CC) $(CFLAGS) tests/*.c *.c $(LDFLAGS) -o $(COVDIR)/test
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes $(COVDIR)/test

gcov_report: clean test
	@mkdir -p $(COVDIR)
	@lcov --capture --directory $(COVDIR) --output-file $(COVDIR)/test.info $(BRANCHES) $(SUPPRESS)
	@lcov --remove $(COVDIR)/test.info '/usr/include/*' '*/tests/*' '*/tests/*' --output-file $(COVDIR)/test.info $(BRANCHES) $(SUPPRESS) 
	@genhtml $(COVDIR)/test.info --output-directory coverage_report $(BRANCHES) > $(COVDIR)/genhtml.log 2>&1
	@bash tests/coverage.sh $(COVDIR)
	@xdg-open coverage_report/index.html $(SUPPRESS)

clang:
	@clang-format -style=Google -n *.c *.h

fixclang:
	@clang-format -style=Google -i *.c *.h

cppcheck:
	@cppcheck --enable=all *.c *.h --suppress=unusedFunction --suppress=missingIncludeSystem

clean:
	@rm -f *.o *.a $(COVDIR)/*.gcno $(COVDIR)/*.gcda $(COVDIR)/*.info *.out *.gcov m/main
	@rm -rf coverage_report $(COVDIR) .clang-format test $(COVDIR)/test


.PHONY: all clean $(TARGET)