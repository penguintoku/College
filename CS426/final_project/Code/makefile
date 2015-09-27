COMPILER = g++
FLAGS = -g -Wall -std=c++0x -O2
EXECUTABLE = lab

all: Driver.o Community.o House.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) Driver.o Community.o House.o

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

Community.o: Community.cpp
	$(COMPILER) $(FLAGS) -c Community.cpp

House.o: House.cpp
	$(COMPILER) $(FLAGS) -c House.cpp

clean:
	rm -f *.o $(EXECUTABLE)
