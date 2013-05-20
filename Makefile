CC = gcc

CCPOTS = -03 -Wall

CFILES = dla-dongkeun.c dtimer.o

CFLAGS = -lm

all: dla

dla: $(CFILES) dtimer.o
	$(CC) -o dla $(CFILES) $(CFLAGS)

dtimer.o : dtimer.c
	$(CC) $(CCOPTS) -c dtimer.c

lint:
	lint -abchp $(CFILES)

