CS442 Design Patterns
Spring 2014
PROJECT 1 README FILE

Due Date: Thursday, February 27, 2014
Submission Date: Thursday, February 27, 2014
Grace Period Used This Project: 0 Days
Grace Period Remaining: 0 Days
Author(s): MW and Tokumaru Yahashi
e-mail(s): mw and tyahash1@binghamton.edu


PURPOSE:

	The purpose of this project is:
		1. Not to use Eclipse
		2. Write code as interfaces

	The code will display the full list of results if the names are in the list.
	If the names are not in the list, it will not display.


PERCENT COMPLETE:

	* We beleive we have completed 100% of the project.


PARTS THAT ARE NOT COMPLETE:

	* None


BUGS:

	* None


FILES:

	There is a total of 16 files for this project:

		build.xml, the file that will compile the code and run
			~ The code where you change the arguments
		dataFile, has 500 lines of names and course numbers
			~ Format: firstName lastName InstructorName courseNumber
			~ All strings are UNIQUE = NO same names in the file
		README.txt, the current file you are reading that has all information
		
		searchFile, the file that will be read to search the names
		PopulateWorker.java, reads in the dataFile and creates the necessary threads
			~ The amount of threads are depended on the arguments in build.xml
		SearchWorker.java, reads in the searchFile and creates the necessary threads
			~ The amount of threads are depended on the arguments in build.xml
		StudentInfo.java, The template of how all the student information will be
		ThreadPopulateWorker.java, reads each line from dataFile and puts information into a vector 
		ThreadSearchWorker.java, reads each line from searchFile and search for matched through the vector

		DataStorage.java, an interface that get and set the vector of student information template
		SexyCode.java, an interface that will be OUR PERSONAL TAG for this year
			~ This interface will not do anything! 
		ThreadCreator.java, an interface that will create threads

		Logger.java, the class that will display all message depending on the DEBUG_LEVEL
			~ The DEBUG_LEVEL is determined by the arguments in build.xml
		RegistrationStore.java, file that contains a vector of student information template for the dataFile.
		Results.java, file that contains a vector and displays the results from searchFile.


SAMPLE OUTPUT:

	Tokumarus-MacBook-Pro:Assignment1 tyahashi$ ant compile
	Buildfile: /Users/tyahashi/Desktop/Assignment1/build.xml

	prepare:
	    [mkdir] Created dir: /Users/tyahashi/Desktop/Assignment1/build
	    [mkdir] Created dir: /Users/tyahashi/Desktop/Assignment1/build/classes

	csRegs:
	    [javac] Compiling 12 source files to /Users/tyahashi/Desktop/Assignment1/build/classes

	compile:

	BUILD SUCCESSFUL
	Total time: 0 seconds
	Tokumarus-MacBook-Pro:Assignment1 tyahashi$ ant run
	Buildfile: /Users/tyahashi/Desktop/Assignment1/build.xml

	jar:
	    [mkdir] Created dir: /Users/tyahashi/Desktop/Assignment1/build/jar
	      [jar] Building jar: /Users/tyahashi/Desktop/Assignment1/build/jar/csRegs.jar

	run:
	     [java] [Alexandria Williamson Jimenez 24
	     [java] , Matthew Mooney Campbell 363
	     [java] , Zion Kirby Acosta 498
	     [java] , Elise Sharp George 166
	     [java] , Gavin Salas Frank 193
	     [java] ]

	BUILD SUCCESSFUL
	Total time: 0 seconds


TO COMPILE:

	* Extract the directories
	* Go to the directory of Assignment1
	* run "ant compile" to compile


TO RUN:

	* run "ant run" to run the code
	*** TO CHANGE THE ARGUMENTS YOU MUST CHANGE IT IN THE FILE build.xml ***
		~ You will need to re-compile everytime you change the arguments


EXTRA CREDIT:

	* N/A (Unless you count not using Eclipse)


BIBLIOGRAPHY:

This serves as evidence that we are in no way intending Academic Dishonesty.
Matthew L Williamson and Tokumaru Yahashi

	* http://docs.oracle.com/javase/7/docs/api/


ACKNOWLEDGEMENT:

	During the coding process one or more of the following people may have been
	consulted. Their help is greatly appreciated.

	Karl
	Brian