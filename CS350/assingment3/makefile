#Tokumaru Yahashi
# Specifiy the target
all: matrixMult.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
matrixMult.exe:matrixMult.o 
	g++ matrixMult.o -lpthread -o matrixMult.exe

# Specify how the object files should be created from source files
matrixMult.o: matrixMult.cpp
	g++ -c -Wall -Wextra -lpthread matrixMult.cpp 

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o *~ matrixMult.exe a.out
