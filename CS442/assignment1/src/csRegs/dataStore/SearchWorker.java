package csRegs.dataStore;

import csRegs.util.Logger;
import csRegs.util.RegistrationStore;
import csRegs.util.Results;

import csRegs.interfaces.SexyCode;
import csRegs.interfaces.ThreadCreator;
import csRegs.interfaces.DataStorage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;

import java.io.FileNotFoundException;

import java.util.Arrays;

/**
 *
 * Will read in a file and create threads depending on the arguments in
 * build.xml. Each thread created will search through the searchFile 
 * starting at different places. Each thread will wait until the 
 * other thread is done.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class SearchWorker implements SexyCode, ThreadCreator {

	private int MM;
	private String searchFile;
	private DataStorage fileProcessor;
	private DataStorage results;

	/**
	 * Empty Constructor 
	 */

	public SearchWorker(){
		Logger.dump(4,"Constructor for SearchWorker called.");
	}

	/**
	 * Explict Constructor
	 *
	 * @param MM				The number of threads created depending on command line
	 * @param searchFile		The file containing all of the names and number to search
	 * @param fileProcessor		Calls a vector containing the infromation
	 * @param results			Looks through the vector and puts in the results  
	 */

	public SearchWorker(int MM, String searchFile, DataStorage fileProcessor, DataStorage results ) {
		this.MM = MM;
		this.searchFile = searchFile;
		this.fileProcessor = fileProcessor;
		this.results = results;  
		Logger.dump(4,"Constructor for SearchWorker called.");  
	}

	/**
	 * createThreads
	 *
	 * Will read in a file once and create multiple threads depending on the arguments
	 * given at the command line. After starting the thread, will join for syncronize.
	 * 
	 * @exception InterruptedException	If the threads don't join
	 * @exception FileNotFoundException If the file doesn't exists
	 */

	public void createThreads(){
		try{		
			BufferedReader searchReader = new BufferedReader(new FileReader(new File(searchFile)));
			Thread[] threads = new Thread[MM];
			for(int i = 0; i < MM; i++){
				Runnable pop = new ThreadSearchWorker(fileProcessor, results, searchReader);
				threads[i] = new Thread(pop);
				threads[i].start();	
			}
			for(int i = 0; i < MM; i++){
				try{
					threads[i].join();
				} catch(InterruptedException exception){
					Logger.dump(0, "Crashed in Search worker, InterruptedException");
					System.exit(1);
				}
			}
		} catch(FileNotFoundException exception){
			Logger.dump(0, "Crashed in Search worker, FileNotFoundException");
			System.exit(1);
		}	
	}
	
	@Override
	public String toString(){
		return "SearchWorker: " + this.MM + " " + this.searchFile + " " + this.fileProcessor + " " + this.results + "\n";
	}
}
