CC=g++
CFLAGS=

all: system.o
	$(CC) main.cpp system.o $(CFLAGS) -o testrun

debug: clean debug_set all

debug_set: 
	$(eval CFLAGS := -DDEBUG)

system.o:	
	$(CC) -c system.cpp thread.cpp utils.cpp $(CFLAGS)

clean:
	-rm *.o

force: clean
	$(CC) main.cpp system.cpp thread.cpp utils.cpp $(CFLAGS) -o testrun

dforce: debug_set force
