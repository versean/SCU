CC	= gcc
CFLAGS	= -g -Wall
LDFLAGS	=
PROGS	= unique_unsorted parity_unsorted unique_sorted parity_sorted

all:			$(PROGS)

clean:;			$(RM) $(PROGS) *.o core

unique_unsorted:	unique.o unsorted.o
			$(CC) -o $@ $(LDFLAGS) unique.o unsorted.o

unique_sorted:		unique.o sorted.o
			$(CC) -o $@ $(LDFLAGS) unique.o sorted.o

parity_unsorted:	parity.o unsorted.o
			$(CC) -o $@ $(LDFLAGS) parity.o unsorted.o

parity_sorted:		parity.o sorted.o
			$(CC) -o $@ $(LDFLAGS) parity.o sorted.o