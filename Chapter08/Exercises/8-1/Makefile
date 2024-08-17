CC = gcc
CFLAGS = -Wall -Wextra -O2

all: cat_high_level cat_low_level generate_input speed_test

cat_high_level: cat_high_level.c
	$(CC) $(CFLAGS) -o $@ $<

cat_low_level: cat_low_level.c
	$(CC) $(CFLAGS) -o $@ $<

generate_input: generate_input.c
	$(CC) $(CFLAGS) -o $@ $<

speed_test: speed_test.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f cat_high_level cat_low_level generate_input speed_test *.o input.txt

test: all
	./generate_input input.txt 1024  # Generate 1GB file
	@echo "Running speed test..."
	./speed_test input.txt

.PHONY: all clean test