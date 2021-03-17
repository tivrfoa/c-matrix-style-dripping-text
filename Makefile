
CC=clang
# CC=gcc
CFLAGS=-g -Wall
OBJS=main.o matrix.o ui.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o main

