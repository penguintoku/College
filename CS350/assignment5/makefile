#Tokumaru Yahashi
# Specifiy the target
all: RWM.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
RWM.exe:RWM.o 
	g++ RWM.o -g -pthread -Wall -Wextra -o RWM.exe

# Specify how the object files should be created from source files
RWM.o: RWM.cpp
	g++ -c -g -pthread -Wall -Wextra RWM.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o *~ RWM.exe a.out
