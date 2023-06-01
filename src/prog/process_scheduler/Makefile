### ------------
TARGET := process-scheduler
### -------------

CC     := gcc
CFLAGS := -Wall -g

SRCDIR := src
SRCS   := $(wildcard $(SRCDIR)/*.c)
OBJS   := $(SRCS:.c=.o)

INPUT  := input.txt
ALG    := FIFO SJF PR RR

define printTestBanner
	@echo "---------------------------------------------"
	@echo "./$(TARGET) -alg $(1) -input $(INPUT)"
	@echo "---------------------------------------------"
endef

README := README.md
META_DASH := ---
META_NAME := name: process-scheduler
META_DESCRIPTION := description: A CLI program simulates process scheduling.


.PHONY: all clean build test-FIFO test-SJF test-PR test-RR

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

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

clean:
	rm -f $(OBJS)
	rm $(TARGET) 

build: $(TARGET)
	rm -f $(OBJS)

# Testing the Program 
test: $(TARGET) test-FIFO test-SJF test-PR test-RR

test-FIFO: $(TARGET)
	$(call printTestBanner,$(word 1, $(ALG)))
	@./$(TARGET) -alg $(word 1, $(ALG)) -input $(INPUT)

test-SJF: $(TARGET)
	$(call printTestBanner,$(word 2, $(ALG)))
	@./$(TARGET) -alg $(word 2, $(ALG)) -input $(INPUT)

test-PR: $(TARGET)
	$(call printTestBanner,$(word 3, $(ALG)))
	@./$(TARGET) -alg $(word 3, $(ALG)) -input $(INPUT)

test-RR: $(TARGET)
	$(call printTestBanner,$(word 4, $(ALG)))
	@./$(TARGET) -alg $(word 4, $(ALG)) -input $(INPUT)
