# Copyright Dobre Andrei-Teodor 314CA 2023-2024

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c allocations.c operations.c -lm -o my_octave

pack:
	zip -FSr 314CA_DobreAndrei-Teodor_Tema2.zip README.md README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
