CC=g++
CFLAGS=-Wall -O3 -c
PROG=airport
OBJS=LQueue.o runway.o

airport: $(OBJS)
	$(CC) -o $(PROG) -c  $(OBJS)
.C.o:
	$(CC) $(CFLAGS) $*.C
LQueue.o:	LQueue.h

runway.o:	runway.h

clean:
	rm *.o core
