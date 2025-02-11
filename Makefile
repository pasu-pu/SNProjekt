CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99 -O2 -D_POSIX_C_SOURCE=200809L

OBJS = main.o find.o list.o stats.o

all: myfind

myfind: $(OBJS)
	$(CC) $(CFLAGS) -o myfind $(OBJS)

main.o: main.c find.h list.h stats.h
	$(CC) $(CFLAGS) -c main.c

find.o: find.c find.h list.h stats.h
	$(CC) $(CFLAGS) -c find.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f $(OBJS) myfind

.PHONY: all clean

