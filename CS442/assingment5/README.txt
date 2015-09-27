CS442 Design Patterns
Spring 2014
PROJECT 5 README FILE

Due Date: 
Submission Date: 
Grace Period Used This Project: 0 Days
Grace Period Remaining: 2 Days
Author(s): Tokumaru Yahashi
e-mail(s): tyahash1@binghamton.edu


PURPOSE:

	The purpose of this project is:
		
		* create two visitors and apply it to two different elements.
		* In other words get familiar with the Visitor Pattern.
		* Not to use Eclipse.


PERCENT COMPLETE:

	* I beleive I have completed 100% of the project.


PARTS THAT ARE NOT COMPLETE:

	* None


BUGS:

	* None


FILES:

	There is a total of 13 files for this project:

		build.xml, the file that will compile the code
				
		README.txt, the current file you are reading that has all the information

		Driver.java, the Driver class that will run the program

		Logger.java, the class that will display all message depending on the DEBUG_LEVEL

		FileProcessor.java, takes in the file and reads in each number

		List.java, the interface for the elements

		MyArrayList.java, an arraylist (one of the ADT required)

		MyVector.java, a vector (one of the ADT required)

		SlowInsertVisitor.java, inserts an element at the end and sorts

		SortedInsertVisitor.java, inserts an element in the correct spot

		testData50.txt, file containing 50 numbers (used for testing)

		testData10.txt, file containing 10 numbers (used for testing)

		Visitor.java, the interface for visitors
		

SAMPLE OUTPUT:

     [java] Displaying arraylist of SortedInsertVisitor
     [java] 114
     [java] 481
     [java] 510
     [java] 515
     [java] 528
     [java] 621
     [java] 630
     [java] 706
     [java] 740
     [java] 933
     [java] Displaying arraylist of SlowInsertVisitor
     [java] 114
     [java] 481
     [java] 510
     [java] 515
     [java] 528
     [java] 621
     [java] 630
     [java] 706
     [java] 740
     [java] 933
     [java] Displaying vector of SortedInsertVisitor
     [java] 114
     [java] 481
     [java] 510
     [java] 515
     [java] 528
     [java] 621
     [java] 630
     [java] 706
     [java] 740
     [java] 933
     [java] Displaying vector of SlowInsertVisitor
     [java] 114
     [java] 481
     [java] 510
     [java] 515
     [java] 528
     [java] 621
     [java] 630
     [java] 706
     [java] 740
     [java] 933
	

LOGGER LEVEL:
	
	0: Regular output
	1: Constructor called
	2: Accept Method called
	3: Visit Method called	
	4: ERROR Messages

TO COMPILE:

	* Extract the directories
	* Go to the directory of Assignment1
	* run "ant compile" to compile


TO RUN:

	* run "ant run" to run


EXTRA CREDIT:

	* N/A (Unless you count not using Eclipse)


BIBLIOGRAPHY:

This serves as evidence that we are in no way intending Academic Dishonesty.
Tokumaru Yahashi

	* http://docs.oracle.com/javase/7/docs/api/


ACKNOWLEDGEMENT:

	During the coding process one or more of the following people may have been consulted. Their help is greatly appreciated.
