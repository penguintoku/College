# Specifiy the target
all: Submission.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
Submission.exe: Submission.o	
	g++ Submission.o  -o Submission.exe

# Specify how the object files should be created from source files
Submission.o: Submission.cpp
	g++  -c -Wall -Wextra Submission.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o Submission.exe