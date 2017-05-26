CC=g++
CFLAGS=-Wall -O3 -c
PROG=LQueue_driver
OBJS=LQueue_driver.o LQueue.o

runway: $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

.C.o:
	$(CC) $(CFLAGS) $*.C

LQueue.o:	LQueue.h

LQueue_driver.o:	LQueue_driver.C LQueue.o LQueue.h

clean:
	rm *.o core
