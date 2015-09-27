package csRegs.dataStore;

import csRegs.util.Logger;
import csRegs.util.RegistrationStore;
import csRegs.util.Results;

import csRegs.interfaces.SexyCode;
import csRegs.interfaces.DataStorage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;

import java.io.IOException;
import java.lang.InterruptedException;

import java.util.Vector;

/**
 *
 * Will get the current line of the file that has the name to add
 * from the file to the vector.
 * Each line will be in the format of: 
 * <p>
 * firstName lastName instructorsName courseNumber
 * <p>
 * and put into a vector.
 * If the file was not split with a single space, it will give error.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class ThreadPopulateWorker implements SexyCode, Runnable {
	private DataStorage fileProcessor;
	private BufferedReader dataReader;

	/**
	 * Empty Constructor
	 */	
	public ThreadPopulateWorker(){
		Logger.dump(4,"Constructor for ThreadPopulateWorker called.");
	}

	/**
	 * Explict Constructor
	 *
	 * @param fileProcessor		Calls a vector containing the infromation
	 * @param dataReader		The sychronized file reader that reads in the data
	 */
    public ThreadPopulateWorker(DataStorage fileProcessor, BufferedReader dataReader){
		this.fileProcessor = fileProcessor;
		this.dataReader = dataReader;
		Logger.dump(4,"Constructor for ThreadPopulateWorker called.");
    }

    /**
	 * Run
	 * 
	 * Will read the file line by line until the the end of file.
	 * For each line, we split it by the " " character into the different data members within StudentInfo and add them.
	 * And then add it to the fileProcessor. 
	 *
	 * @exception IOException 	Will be thrown if there is an input/output error
	 */
    public synchronized void run(){
		try{
			Logger.dump(3,"ThreadPopulateWorker run method called.");
			String currentLine = "";			
			while((currentLine = dataReader.readLine()) != null){
				String values[] = currentLine.split(" ");
 	
				StudentInfo student = new StudentInfo();
				student.setFirstName(values[0]);
				student.setLastName(values[1]);
				student.setInstructorName(values[2]);
				student.setCourseNumber(Integer.parseInt(values[3]));
				
				fileProcessor.getData().add(student);
			}
		} catch(IOException exception){
			Logger.dump(0, "Crashed in Populate worker, IOException");			
			System.exit(1);
		} 
    }

	@Override
	public String toString(){
		return "ThreadPopulateWorker: " + this.fileProcessor + " " + this.dataReader + "\n";
	}
}
