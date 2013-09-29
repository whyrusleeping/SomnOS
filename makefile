#one makefile to rule them all
CC=g++
OPTLEVEL=0
DEFINES=
FLAGS=-Wall -Werror -O$(OPTLEVEL) -g $(DEFINES)
LIBS=
PROG_NAME=somn
OBJDIR=obj
SRCDIR=src
BINDIR=bin

SRCS = instruction.cpp \
	   thread.cpp \
	   utils.cpp \
	   system.cpp \
	

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CC) $(FLAGS) -c -o $@ $<

all: $(OBJS)
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
	$(CC) $(FLAGS) -c -o $(OBJDIR)/main.o $(SRCDIR)/main.cpp
	$(CC) $(FLAGS) $(LIBS) $(OBJS) $(OBJDIR)/main.o -o $(BINDIR)/$(PROG_NAME)

test: $(SRCDIR)/instructionTest.cpp $(OBJS)
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
	$(CC) $(FLAGS) $(LIBS) $(OBJS) $(SRCDIR)/instructionTest.cpp -o $(BINDIR)/tests
	bin/tests

clean:
	rm -rf $(OBJDIR) $(BINDIR)
