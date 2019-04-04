# Make file for C++
CC = g++
CFLAG = -g -Wall
EXE = proj2

# Unzip and Compile, & allow for EXE to be executed
all : $(EXE)
	chmod +x $(EXE)

# Compiles all .o files
$(EXE) : CommandReader.o Element.o Heap.o Main.o Util.o Graph.o Node.o LinkedList.o
	$(CC) $(CFLAG) -o $@ $+ -lm

# Builds .o files based on the .cpp and .h files
%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Removes all object files
clean :
	rm -f *.o
