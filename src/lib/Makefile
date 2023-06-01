# ----- Compiler
CC := gcc
# ----- Flags
FLAG_REG := -Wall -g
FLAG_MM  := -MM
# ----- Driver 
MAIN_C := main.c
MAIN_O := main.o
EXE    := main
# ----- 
PREREQ := $(shell $(CC) $(FLAG_MM) $(MAIN_C))
temp   := $(filter-out $(MAIN_O):, $(PREREQ))
PREREQ := $(temp)
# $(foreach var,list,text) $(var:pattern=replacement)
C_SRCS := $(foreach p,$(PREREQ),$(p:.h=.c))
temp   := $(foreach p,$(C_SRCS),$(p:.c=.o))
OBJS   := $(filter-out $(MAIN_O):, $(temp))
all: $(EXE)

main.o: $(C_SRCS)
	$(CC) $(FLAG_REG) -c $^

$(EXE): $(OBJS)
	$(CC) $(FLAG_REG) -o $@ $^

clean:
	rm *.o $(EXE)

# Testing -------------------------------------------------- 

test :
	@echo "PREREQ: "$(PREREQ)
	@echo "C_SRCS: "$(C_SRCS)
	@echo "OBJS:   "$(OBJS)

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
