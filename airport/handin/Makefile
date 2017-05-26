CC=g++
CFLAGS=-Wall -O3
PROG=AirportSimulator
OBJS=LQueue.o Runway.o Airport.o

AirportSimulator: LQueue.o Runway.o Airport.o
	$(CC)  $(OBJS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm *.o core
