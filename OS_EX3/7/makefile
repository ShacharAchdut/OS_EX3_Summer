CC=g++
CFLAGS=-Wall -g -I.  # -I. to include the current directory

all: server

server: server.o proactor.o
	$(CC) $(CFLAGS) server.o proactor.o -o server

server.o: server.cpp  # No need to add ConvexHall.hpp here
	$(CC) -c $(CFLAGS) server.cpp	

proactor.o: proactor.cpp  # Ensure proactor.cpp is present in the same directory
	$(CC) -c $(CFLAGS) proactor.cpp		

clean:
	rm -f *.o server
