# ==================================================
TARGET_C    = main
TARGET_JAVA = Main
TEST_ARG    = 20000
# ==================================================

# ========== All ==========

all: $(TARGET_C) $(TARGET_JAVA)

.PHONY: clean vg test-c test-java test-all

test-all: test-c test-java

clean: clean-c clean-java

# ========== C ==========

CC = gcc
CFLAGS = -Wall -g -pthread

C_SRC = $(wildcard *.c)
C_OBJ = $(C_SRC:.c=.o)

$(TARGET_C): $(C_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

vg: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET_C) $(TEST_ARG)

test-c: all
	./$(TARGET_C) $(TEST_ARG)

clean-c:
	rm -f $(C_OBJ) $(TARGET_C)

# ========== Java ==========

JAVAC = javac
JAVA_SRC = $(wildcard *.java)
JAVA_OBJ = $(JAVA_SRC:.java=.class)

$(TARGET_JAVA): $(JAVA_OBJ)

%.class: %.java
	$(JAVAC) $<

test-java: $(TARGET_JAVA)
	java $(TARGET_JAVA) $(TEST_ARG)

clean-java:
	rm -f $(JAVA_OBJ)
