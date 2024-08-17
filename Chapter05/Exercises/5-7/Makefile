CC = clang
CFLAGS = -Wall -std=c99 -g

PROG1 = alloc_version
PROG2 = main_version
GEN_INPUT = rand_input

all: $(PROG1) $(PROG2) $(GEN_INPUT)

$(PROG1): $(PROG1).c
	$(CC) $(CFLAGS) -o $@ $^

$(PROG2): $(PROG2).c
	$(CC) $(CFLAGS) -o $@ $^

$(GEN_INPUT): $(GEN_INPUT).c
	$(CC) $(CFLAGS) -o $@ $^

test:
	@echo "Generating input..."
	@./$(GEN_INPUT) > temp_input.txt
	@echo "Testing alloc version with generated input:"
	@time (./$(PROG1) < temp_input.txt > /dev/null)
	@echo "Testing main version with generated input:"
	@time (./$(PROG2) < temp_input.txt > /dev/null)
	@rm temp_input.txt

clean:
	rm -f $(PROG1) $(PROG2) $(GEN_INPUT) temp_input.txt

.PHONY: all test clean

