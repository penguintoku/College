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
 * Will get the current line of the file that has the name to search.
 * If the name was in the data file, it will pull out the whole
 * infromation in the format of:
 * <p>
 * firstName lastName instructorsName courseNumber
 * <p>
 * and put into a vector of results.
 * If the name was NOT in the data, it will not put anthing in the
 * vector.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class ThreadSearchWorker implements SexyCode, Runnable {
	private DataStorage fileProcessor;
	private DataStorage results;
	private BufferedReader searchReader;


	/**
	 * Empty Constructor
	 */
	public ThreadSearchWorker(){
		Logger.dump(4,"Constructor for ThreadSearchWorker called.");
	}

	/**
	 * Explict Constructor
	 *
	 * @param fileProcessor		Calls a vector containing the infromation
	 * @param results 			Will display the matches between the data file and the search file
	 * @param searchReader		The sychronized file reader that reads in the search data
	 */
    public ThreadSearchWorker(DataStorage fileProcessor, DataStorage results, BufferedReader searchReader){
		this.fileProcessor = fileProcessor;
		this.results = results;
		this.searchReader = searchReader;
		Logger.dump(4,"Constructor for ThreadSearchWorker called.");
	}

	/**
	 * Run
	 * 
	 * Will read the file line by line until the the end of file.
	 * For each line, we split it by the " " character into the different data members within StudentInfo and add them.
	 * And then add it to the fileProcessor if that data is found within the fileProcessor.
	 *
	 * @exception IOException 	Will be thrown if there is an input/output error
	 */
	public synchronized void run(){
		try{
			Logger.dump(3,"ThreadSearchWorker run method called.");
			String currentLine = "";			
			while((currentLine = searchReader.readLine()) != null){ 	
				StudentInfo student = new StudentInfo();
				student.setFirstName(currentLine);
		
				
				for(int i = 0; i< fileProcessor.getData().size(); i++){
					if(fileProcessor.getData().get(i).getFirstName().equals(student.getFirstName()) 
						|| fileProcessor.getData().get(i).getLastName().equals(student.getFirstName())
						|| fileProcessor.getData().get(i).getInstructorName().equals(student.getFirstName())){					
						results.getData().add(fileProcessor.getData().get(i));
						Logger.dump(2,"ThreadSearchWorker added a StudentInfo object to the Result's vector.");
					}	
				}
			}
		} catch(IOException exception){
			Logger.dump(0, "Crashed in Search worker, IOException");			
			System.exit(1);
		} 
    }

	@Override
	public String toString(){
		return "ThreadSearchWorker: " + this.fileProcessor + " " + this.results + " " + this.searchReader + "\n";
	}
}