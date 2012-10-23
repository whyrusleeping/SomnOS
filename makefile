CC=g++
CFLAGS=

all: system.o
	$(CC) main.cpp system.o $(CFLAGS) -o testrun

debug: clean debug_set all

debug_set: 
	$(eval CFLAGS := -DDEBUG)

system.o:
	$(CC) -c system.cpp $(CFLAGS)

clean:
	rm *.o
