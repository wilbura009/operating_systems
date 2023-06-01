# ----- Compiler
CC := gcc
# ----- Flags
FLAG_REG := -Wall -g
FLAG_MM  := -MM
# ----- Compiler Command String
CC_CMD_STR := $(CC) $(FLAG_REG)

# ----- Parts
P1_EXE := part1
P1_C := $(addsuffix .c,$(P1_EXE))
P1_O := $(addsuffix .o,$(P1_EXE))
# ----- 
P1_REQ := $(shell $(CC) $(FLAG_MM) $(P1_C))
temp   := $(filter-out $(P1_O):, $(P1_REQ))
P1_REQ := $(temp)
# $(foreach var,list,text) $(var:pattern=replacement)
P1_C_SRCS := $(foreach p,$(P1_REQ),$(p:.h=.c))
temp   := $(foreach p,$(P1_C_SRCS),$(p:.c=.o))
P1_OBJS   := $(filter-out $(P1_O):, $(temp))

P2_EXE := part2
P2_C := $(addsuffix .c,$(P2_EXE))
P2_O := $(addsuffix .o,$(P2_EXE))
# ----- 
P2_REQ := $(shell $(CC) $(FLAG_MM) $(P2_C))
temp   := $(filter-out $(P2_O):, $(P2_REQ))
P2_REQ := $(temp)
# $(foreach var,list,text) $(var:pattern=replacement)
P2_C_SRCS := $(foreach p,$(P2_REQ),$(p:.h=.c))
temp   := $(foreach p,$(P2_C_SRCS),$(p:.c=.o))
P2_OBJS   := $(filter-out $(P2_O):, $(temp))

# ----- Valgrind
VALGRIND := valgrind --leak-check=full -s
# ----- ouput files
OUTPUTS := part1-output part1-out-test part2-output
# ----- input files
INPUTS := part1testsequence part1sequence part2sequence
#  ----- Targets
EXES := $(P1_EXE) $(P2_EXE)
# ----- MD5 Hashes from http://www.cs.utsa.edu/~korkmaz/teaching/resources-os-ug/tk-assign/assign3.html
#                    P1                                   P2
TARGET_HASHES := ceabc02825a5b908e474b053074ab53c c95b27848ae8d4354d87678d075001f7 

# --- Compile and Link the targets
all: $(P1_EXE) $(P2_EXE)

$(P1_O): $(P1_C_SRCS)
	$(CC) $(FLAG_REG) -c $^

$(P1_EXE): $(P1_OBJS)
	$(CC) $(FLAG_REG) -o $@ $^

$(P2_O): $(P2_C_SRCS)
	$(CC) $(FLAG_REG) -c $^

$(P2_EXE): $(P2_OBJS)
	$(CC) $(FLAG_REG) -o $@ $^

# ----- Run the targets
run: $(P1_EXE) $(P2_EXE)
	@echo
	@echo "Part 1:"
	./$(P1_EXE) $(word 1, $(INPUTS)) part1-out-test -v
	@echo
	@echo "Part 2:"
	./$(P1_EXE) $(word 2, $(INPUTS)) part1-output
	md5sum part1-output
	@echo
	./$(P2_EXE) $(word 3, $(INPUTS)) part2-output
	md5sum part2-output

hash-diff:
	@mkdir hashes
	# ============================== Part 1 ============================== 
	# --- Print the target and actual hashes
	@echo "Target: " $(word 1, $(TARGET_HASHES))
	@echo "Actual: " $(shell md5sum part1-output | cut -d ' ' -f 1)
	@echo
	# --- Use diff to compare the hashes
	@echo $(word 1, $(TARGET_HASHES)) > ./hashes/p1-target.hash
	@echo $(shell md5sum part1-output | cut -d ' ' -f 1) > ./hashes/p1-actual.hash
	diff -s ./hashes/p1-target.hash ./hashes/p1-actual.hash
	@echo
	# ============================== Part 2 ============================== 
	# --- Print the target and actual hashes
	@echo "Target: " $(word 2, $(TARGET_HASHES))
	@echo "Actual: " $(shell md5sum part2-output | cut -d ' ' -f 1)
	@echo
	# --- Use diff to compare the hashes
	@echo $(word 2, $(TARGET_HASHES)) > ./hashes/p2-target.hash
	@echo $(shell md5sum part2-output | cut -d ' ' -f 1) > ./hashes/p2-actual.hash
	diff -s ./hashes/p2-target.hash ./hashes/p2-actual.hash
	@echo
	# --- Clean created hashes
	rm -r ./hashes

.PHONY: vg test-make clean-obj clean-exe clean-ouput clean all

clean-obj:
	for obj in $(P1_OBJS) $(P2_OBJS); do \
		if [ -f $$obj ]; then rm -f $$obj; fi; \
	done

clean-exe:
	for exe in $(EXES); do \
		if [ -f $$exe ]; then rm -f $$exe; fi; \
	done

clean-output:
	for output in $(OUTPUTS); do \
		if [ -f $$output ]; then rm -f $$output; fi; \
	done

clean: clean-obj clean-exe clean-output

test-make:
	@echo "CC_CMD_STR:    "$(CC_CMD_STR)
	@echo "P1_EXE:        "$(P1_EXE)
	@echo "P1_C:          "$(P1_C)
	@echo "P1_O:          "$(P1_O)
	@echo "P1_REQ:        "$(P1_REQ)
	@echo "P1_C_SRCS:     "$(P1_C_SRCS)
	@echo "P1_OBJS:       "$(P1_OBJS)
	@echo "P2_EXE:        "$(P2_EXE)
	@echo "P2_C:          "$(P2_C)
	@echo "P2_O:          "$(P2_O)
	@echo "P2_REQ:        "$(P2_REQ)
	@echo "P2_C_SRCS:     "$(P2_C_SRCS)
	@echo "P2_OBJS:       "$(P2_OBJS)
	@echo "OUTPUTS:       "$(OUTPUTS)

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
