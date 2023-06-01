### --- Driver --------- ###
TARGET := main
INPUT  := input.txt
### -------------------- ###

# --- Compiler
CC = gcc

# --- Flags
CFLAGS = -Wall -g
#CFLAGS_THREAD = -Wall -g -l pthread

# --- Directories
SRC_DIR = src

# --- Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC_FILES:.c=.o)

# --- Memeory Check
VALGRIND := valgrind --leak-check=full -s --track-origins=yes

README := README.md
META_DASH := ---
META_NAME := name: address_calculator
META_DESCRIPTION := description: A CLI program that calculates paging infomation.

.PHONY: all clean test-fifo test-lru test-memory-fifo test-memory-lru

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

test: test-fifo test-lru

test-fifo: $(TARGET)
	./$(TARGET) -fifo $(INPUT)

test-lru: $(TARGET)
	./$(TARGET) -lru $(INPUT)

test-memory-fifo: $(TARGET)
	$(VALGRIND) ./$(TARGET) -fifo $(INPUT)

test-memory-lru: $(TARGET)
	$(VALGRIND) ./$(TARGET) -lru $(INPUT)

# ---------- Reference -----------
#
# $(RM) = rm -f 
#
# ----- Generate .o
# gcc -c main.c restart.c errExit.c 
# ----- Link .o
# gcc -o main main.o restart.o errExit.o
#
# Automatic Variables:
# --------------------
# $^ : Get list of all prerequisites
# $< : Get first prerequisite 
# $@ : Get target value
#
# Execute another target in a recipe:
# -----------------------------------
# THIS_FILE := $(lastword $(MAKEFILE_LIST))
# $(MAKE) -f $(THIS_FILE) all # This goes in the recipe
