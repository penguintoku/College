#Tokumaru Yahashi

# Specifiy the target
all: PCwithThreads.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
PCwithThreads.exe:PCwithThreads.o 
	g++ PCwithThreads.o -lpthread -o PCwithThreads.exe

# Specify how the object files should be created from source files
PCwithThreads.o: PCwithThreads.cpp
	g++ -c -lpthread PCwithThreads.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o *~ PCwithThreads.exe a.out