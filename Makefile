SRC = $(wildcard src/*.c)
CFLAGS = -std=c99 -Wall -Wcomment

all:
	gcc -o em $(CFLAGS) $(SRC)

.PHONY: all
