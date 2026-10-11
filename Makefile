CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

all: main

main: main.c src/Dict.c include/Dict.h
	$(CC) $(CFLAGS) -o $@ main.c src/Dict.c

tests/test_dict: tests/test_dict.c src/Dict.c include/Dict.h
	$(CC) $(CFLAGS) -o $@ tests/test_dict.c src/Dict.c

test: tests/test_dict
	./tests/test_dict

clean:
	rm -f main main.exe tests/test_dict tests/test_dict.exe

.PHONY: all test clean
