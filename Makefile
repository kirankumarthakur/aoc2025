# Compiler Settings
CXX      := clang++
CXXFLAGS := -std=c++23 -O2 -Wall -Wextra -Wpedantic -Werror -Wfloat-equal -Wshadow

# Arguments (defaults)
d ?= 1
p ?= 1
# New argument for passing flags/inputs to the C++ program
r ?=

# Paths
DIR := day$(d)
SRC := $(DIR)/q$(p).cpp
# The binary will be placed inside the Day folder
BIN := runner.exe

.PHONY: run clean help

run:
	@echo "--- Compiling $(SRC) ---"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(DIR)/$(BIN)
	@echo "--- Executing inside $(DIR)/ ---"
	@# We pass $(r) to the binary here
	@(cd $(DIR) && ./$(BIN) $(r))

clean:
	rm -f Day*/$(BIN)

# Help command to show usage
help:
	@echo "Usage:"
	@echo "  make d=<day> p=<part> [r=\"<arguments>\"]"
	@echo ""
	@echo "Examples:"
	@echo "  make d=01 p=1                 -> Runs day1/q1.cpp with no r"
	@echo "  make d=05 p=2 r=\"input.txt\" -> Runs day5/q2.cpp passing 'input.txt'"