package csRegs.driver;

import csRegs.util.Logger;
import csRegs.util.RegistrationStore;
import csRegs.util.Results;

import csRegs.dataStore.PopulateWorker;
import csRegs.dataStore.SearchWorker;

import csRegs.interfaces.SexyCode;
import csRegs.interfaces.ThreadCreator;
import csRegs.interfaces.DataStorage;

/**
 * The Driver code where the code will run. 
 * It will take in the arguments given by build.xml
 * Implemented the whole code as interfaces so no concrete.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */ 
public class Driver implements SexyCode {

	public static void main(String args[]) {
	
	String dataFile = args[0];
	int	NN = Integer.parseInt(args[1]);
	String searchFile = args[2];
	int	MM = Integer.parseInt(args[3]);
	int DEBUG_VALUE = Integer.parseInt(args[4]);
	Logger.setLevel(DEBUG_VALUE);

	if((NN > 5 || NN < 1) || (MM > 5 || MM < 1) || (DEBUG_VALUE > 4 || DEBUG_VALUE < 0)){
		Logger.dump(0, "Incorrect argument input");
		System.exit(1);
	}
	
	DataStorage fileProcessor = new RegistrationStore();	
	DataStorage results = new Results();

	ThreadCreator populate = new PopulateWorker(NN, dataFile, fileProcessor);
	populate.createThreads();
	ThreadCreator search = new SearchWorker(MM, searchFile, fileProcessor, results);
	search.createThreads();
	System.out.println(results);
	}
}
