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
 * build.xml. Each thread created will search through the dataFile once 
 * starting at different places. Each thread will wait until the 
 * other thread is done. No entry will be read more than once.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class PopulateWorker implements SexyCode, ThreadCreator {
	private int NN;
	private String dataFile;
	private DataStorage fileProcessor;

	/**
	 * Empty Constructor
	 */
	public PopulateWorker(){
		Logger.dump(4,"Constructor for PopulateWorker called.");
	}

	/**
	 * Explict Constructor
	 *
	 * @param NN				The number of threads created depending on command line
	 * @param datafile			The file containing all of the names and number
	 * @param fileProcessor		Calls a vector containing the infromation
	 */
	public PopulateWorker(int NN, String dataFile, DataStorage fileProcessor){
		this.NN = NN;
		this.dataFile = dataFile;
		this.fileProcessor = fileProcessor;
		Logger.dump(4,"Constructor for PopulateWorker called.");
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
			BufferedReader dataReader = new BufferedReader(new FileReader(new File(dataFile)));
			Thread[] threads = new Thread[NN];
			for(int i = 0; i < NN; i++){
				Runnable pop = new ThreadPopulateWorker(fileProcessor, dataReader);
				threads[i] = new Thread(pop);
				threads[i].start();	
			}
			for(int i = 0; i < NN; i++){
				try{
					threads[i].join();
				} catch(InterruptedException exception){
					Logger.dump(0,"Crashed in Populate worker, InterruptedException");
					System.exit(1);
				}
			}
		} catch(FileNotFoundException exception){
			Logger.dump(0, "Crashed in Popualte worker, FileNotFoundException");
			System.exit(1);
		}	
	}

	@Override
	public String toString(){
		return "PopulateWorker: " + this.NN + " " + this.dataFile + " " + this.fileProcessor + "\n";
	}
}
