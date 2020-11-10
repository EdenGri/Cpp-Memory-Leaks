# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11


# All Targets
all: Ass1

# Tool invocations
# Executable "hello" depends on the files hello.o and run.o.
Ass1: bin/main.o bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o 
	@echo 'Building target: Ass1'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/cTrace  bin/main.o bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o
	@echo 'Finished building target: Ass1'
	@echo ' '

# Depends on the source and header files
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

# Depends on the source and header files
bin/Agent.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

# Depends on the source and header files
bin/Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp
# Depends on the source and header files
bin/Session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp
# Depends on the source and header files
bin/Tree.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp

#Clean the build directory
clean: 
	rm -f bin/*
