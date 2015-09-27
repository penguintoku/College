#Tokumaru Yahashi
# Specifiy the target
all: MMwP.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
MMwP.exe:MMwP.o 
	g++ MMwP.o -g -Wall -Wextra -o MMwP.exe

# Specify how the object files should be created from source files
MMwP.o: MMwP.cpp
	g++ -c -g -Wall -Wextra MMwP.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o *~ MMwP.exe a.out
