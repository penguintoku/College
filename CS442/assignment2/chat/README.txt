CS442 Design Patterns
Spring 2014
PROJECT 2 README FILE

Due Date: Thursday, March 13, 2014
Submission Date: Thursday, March 13, 2014
Grace Period Used This Project: 0 Days
Grace Period Remaining: 5 Days
Author(s): MW and Tokumaru Yahashi
e-mail(s): mw and tyahash1@binghamton.edu


PURPOSE:

	The purpose of this project is:
		1. Not to use Eclipse
		2. Make a server and client code to implement a chat program
		3. Make a singleton threadpool for the server connections

	The code will display the full list of results if the names are in the list.
	If the names are not in the list, it will not display.


PERCENT COMPLETE:

	* We beleive we have completed 100% of the project.


PARTS THAT ARE NOT COMPLETE:

	* None


BUGS:

	* None


FILES:

	There is a total of 9 files for this project:

		build.xml, the file that will compile the code
		
		run.sh, a script file to run the code
		
		README.txt, the current file you are reading that has all the information

		SexyCode.java, an interface that will be OUR PERSONAL TAG for this year
			~ This interface will not do anything! 

		Logger.java, the class that will display all message depending on the DEBUG_LEVEL
		
		ThreadPool.java, the class that creates the thread pool for the connection of the sockets

		ServerDriver.java, the main class for the Server which starts the Server
		
		SeverThread.java, displays the menu and takes in the user input on what they would like to do

		ClientDriver.java, the main class for the Client which starts the client and would display the menu and takes in the user input on what they would like to do.


SAMPLE OUTPUT:


	


TO COMPILE:

	* Extract the directories
	* Go to the directory of Assignment1
	* run "ant compile" to compile


TO RUN:

	* In order to run, you need to run the server side first.
	./run.sh Server

	* You can run client once server is established.
	./run.sh Client portNumber
		~ the portNumber will be displayed when you run the Server.

EXTRA CREDIT:

	* N/A (Unless you count not using Eclipse)


BIBLIOGRAPHY:

This serves as evidence that we are in no way intending Academic Dishonesty.
Matthew L Williamson and Tokumaru Yahashi

	* http://docs.oracle.com/javase/7/docs/api/
	* http://docs.oracle.com/javase/tutorial/networking/sockets/clientServer.html


ACKNOWLEDGEMENT:

	During the coding process one or more of the following people may have been consulted. Their help is greatly appreciated.
