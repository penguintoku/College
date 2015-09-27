CS442 Design Patterns
Spring 2014
PROJECT 4 README FILE

Due Date: Thursday, April 24, 2014
Submission Date: Thursday, April 25, 2014
Grace Period Used This Project: 1 Days
Grace Period Remaining: 4 Days for MW, 2 for Tokumaru Yahashi
Author(s): MW and Tokumaru Yahashi
e-mail(s): MW and tyahash1@binghamton.edu


PURPOSE:

	The purpose of this project is:
		1. To use the Dynamic Proxy Pattern to implement methods from two different interfaces
		2. To use Java Reflection to help with deserialization from a file
		3. Use the Tag/Marker Pattern

PERCENT COMPLETE:

	* We beleive we have completed 100% of the project.


PARTS THAT ARE NOT COMPLETE:

	* None


BUGS:

	* None


FILES:

	There is a total of 13 files for this project:

		StoreRestoreHandler.java, our invocation handler for the Dynamic Proxy
		Driver.java, holds the main method which tests the code
		RestoreI.java, is an interface that has the deserialization method
		StoreI.java, is an interface that has the serialization method
		StoreRestoreI.java, is a blank interface used for the Tag/Marker Pattern
		EmployeeRecord.java, is a serializable object
		Logger.java, the class that will display all message depending on the DEBUG_LEVEL
		ProxyCreater.java, is a utility class used to make the proxy
		SerializableObject.java, is a empty class used for the Tag/Marker Pattern
		StudentRecord.java, is a serializable object

		build.xml, the file that will compile the code		
		inputFile.txt, the numbers on each line to test the code
		README.txt, the current file you are reading that has all the information


SAMPLE OUTPUT:
 	
 	[java] They are Equal
    [java] They are Equal
    [java] They are Equal
    [java] They are Equal
    [java] They are Equal
	

TO COMPILE:

	* Extract the directories
	* Go to the directory of Assignment4
	* run "ant compile" to compile


TO RUN:

	* run "ant run"
	* The three values are taken in from the build.xml:  the numOfObjects, the dataFile, and the DEBUG_VALUE


DUBUG_LEVEL:
	* 0: The regular output of the program
	* 1: There is an error that is caught in a catch
	* 2: There is an error that is caught in an if statement
	* 3: The invoke method is called
	* 4: All constructors when instantiated


EXTRA CREDIT:

	* N/A


BIBLIOGRAPHY:

This serves as evidence that we are in no way intending Academic Dishonesty.
Matthew L Williamson and Tokumaru Yahashi

	* http://docs.oracle.com/javase/7/docs/api/
