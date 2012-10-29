# makefile for somnOS VM
# by Jeromy Johnson

# I want to try clang out sometime
CC=g++

CFLAGS=


all: system.o thread.o utils.o
	$(CC) main.cpp system.o thread.o utils.o $(CFLAGS) -o testrun

debug: clean debug_set all

debug_set: 
	$(eval CFLAGS := -DDEBUG)

system.o: 
	$(CC) -c system.cpp  $(CFLAGS)

thread.o:
	$(CC) -c thread.cpp $(CFLAGS)

utils.o:
	$(CC) -c utils.cpp $(CFLAGS)

clean:
	-rm *.o

rebuild: clean all
