# Makefile für das find-Projekt

CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -pthread

SRCS = src/main.c src/find.c src/stats.c src/list.c src/log.c
OBJS = $(SRCS:.c=.o)
TARGET = find

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
    cd tests && ./run_tests.sh

.PHONY: all clean test
