# makefile for somnOS VM
# by Jeromy Johnson

# I want to try clang out sometime
CC=g++

BIN=../bin/
NAME=testrun

CFLAGS=


all: system.o thread.o utils.o instruction.o
	$(CC) main.cpp system.o thread.o utils.o instruction.o $(CFLAGS) -o $(BIN)$(NAME)

debug: clean debug_set all

debug_set: 
	$(eval CFLAGS := -DVERBOSE -g)

system.o: system.cpp
	$(CC) -c system.cpp  $(CFLAGS)

thread.o: thread.cpp
	$(CC) -c thread.cpp $(CFLAGS)

utils.o: utils.cpp
	$(CC) -c utils.cpp $(CFLAGS)

instruction.o: instruction.cpp
	$(CC) -c instruction.cpp $(CFLAGS)

clean:
	-rm *.o

rebuild: clean all


# Start Tests

alltests: clean instructionTest
	./instrTest
	@echo "Success!"


instructionTest: instruction.o
	$(CC) instructionTest.cpp instruction.o $(CFLAGS) -o instrTest
