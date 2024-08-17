CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean