ifeq ($(OS),Windows_NT)
EXEEXT := .exe
else
EXEEXT :=
endif

CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -g
LDLIBS := -lm

PRACTICE_SRC := $(wildcard practice/*.c)
PRACTICE_BIN := $(patsubst practice/%.c,practice/%$(EXEEXT),$(PRACTICE_SRC))
SOLUTION_SRC := $(wildcard solutions/*.c)
SOLUTION_BIN := $(patsubst solutions/%.c,solutions/%$(EXEEXT),$(SOLUTION_SRC))

.DEFAULT_GOAL := practice

practice: $(PRACTICE_BIN)

solutions: $(SOLUTION_BIN)

practice/%$(EXEEXT): practice/%.c
$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

solutions/%$(EXEEXT): solutions/%.c
$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

test: practice
@echo "Running practice tests..."
@for bin in $(PRACTICE_BIN); do echo "--- $$bin ---"; ./$$bin || exit 1; done
@echo "All practice tests passed!"

test-solutions: solutions
@echo "Running solution tests..."
@for bin in $(SOLUTION_BIN); do echo "--- $$bin ---"; ./$$bin || exit 1; done
@echo "All solution tests passed!"

clean:
$(RM) $(PRACTICE_BIN) $(SOLUTION_BIN)

.PHONY: practice solutions test test-solutions clean