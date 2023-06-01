### --- Driver --------- ###
TARGET := address-calculator
### -------------------- ###

# --- Compiler
CC = gcc

# --- Flags
CFLAGS = -Wall -g
#CFLAGS_THREAD = -Wall -g -l pthread

# --- Memeory Check
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND_FULL = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# --- Test Arguments
TEST_ARGS_0 := 16 -mb 128 -kb 2 -kb

README := README.md
META_DASH := ---
META_NAME := name: address_calculator
META_DESCRIPTION := description: A CLI program that calculates paging infomation.

.PHONY: all clean help test valgrind valgrind-full

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

create-readme:
	@echo $(META_DASH) > $(README)
	@echo $(META_NAME) >> $(README)
	@echo $(META_DESCRIPTION) >> $(README)
	@echo $(META_DASH) >> $(README)
	@echo >> $(README)
	@echo "## Usage" >> $(README)
	@echo >> $(README)
	@echo "\`\`\`" >> $(README)
	@$(MAKE) -s help >> $(README)
	@echo "\`\`\`" >> $(README)
	@echo >> $(README)
	@echo "## Test" >> $(README)
	@echo >> $(README)
	@echo "\`\`\`" >> $(README)
	@$(MAKE) test >> $(README)
	@echo "\`\`\`" >> $(README)
	@echo >> $(README)
	@sed -i '/make\[.*\]/d' $(README)
	@$(MAKE) clean

help: $(TARGET)
	./$(TARGET) -h

test: $(TARGET)
	./$(TARGET) $(TEST_ARGS_0)

test-fail: $(TARGET)
	./$(TARGET) $(TEST_ARGS_0) -kb 0

valgrind: $(TARGET)
	$(VALGRIND) ./$(TARGET) $(TEST_ARGS_0)

valgrind-full: $(TARGET)
	$(VALGRIND_FULL) ./$(TARGET) $(TEST_ARGS_0)

test-meta-vars:
	@echo $(META_DASH)
	@echo $(META_NAME)
	@echo $(META_DESCRIPTION)


# ---------- Reference -----------
#
# $(RM) = rm -f
#
# ----- Generate .o
# gcc -c <list_of_c_files>
#
# ----- Link .o
# gcc -o <target> <list_of_o_files>
#
# Automatic Variables:
# --------------------
# $^ : Get list of all prerequisites
# $< : Get first prerequisite
# $@ : Get target value
