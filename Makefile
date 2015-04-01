#
# Makefile for "Kakuro" puzzle solving programa
#

CC = gcc
TARGET = crosssums
FLAGS = -g -ansi -Wall -pedantic -I.

SRCFILES = main.c utils.c puzzle.c tree.c list.c comb.c
INCFILES=  utils.h puzzle.h tree.h list.h item.h
OBJFILES=  main.o comb.o utils.o puzzle.o tree.o list.o

default: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

main.o: main.c utils.h puzzle.h tree.h
	$(CC) -c $(CFLAGS) main.c

tree.o: tree.c tree.h puzzle.h utils.h list.h Item.h
	$(CC) -c $(CFLAGS) tree.c

puzzle.o: puzzle.c puzzle.h utils.h
	$(CC) -c $(CFLAGS) puzzle.c

utils.o: utils.c utils.h puzzle.h
	$(CC) -c $(CFLAGS) utils.c

list.o: list.c list.h Item.h
	$(CC) -c $(CFLAGS) list.c

comb.o: comb.c utils.h
	$(CC) -c $(CFLAGS) comb.c

clean:
	rm -f $(TARGET) $(OBJFILES)

