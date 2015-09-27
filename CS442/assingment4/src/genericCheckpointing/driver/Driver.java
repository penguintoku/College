package genericCheckpointing.driver;

import genericCheckpointing.util.Logger;
import genericCheckpointing.util.ProxyCreator;
import genericCheckpointing.util.SerializableObject;
import genericCheckpointing.util.EmployeeRecord;
import genericCheckpointing.util.StudentRecord;

import genericCheckpointing.server.StoreRestoreI;
import genericCheckpointing.server.StoreI;
import genericCheckpointing.server.RestoreI;

import genericCheckpointing.djsonStoreRestore.StoreRestoreHandler;

import java.lang.reflect.InvocationHandler;

/**
 *
 * Driver class contains the main method for the package
 * The main method goes through and first checks the input to see if it is correct
 * We than make a dynamic proxy using our utility class as well as our invocation handler
 * This proxy uses the StoreI and RestoreI interfaces
 * We than open the file and begin to serialize using java reflection from the file
 * This data is stored in an array for later
 * Than the date that was serialized is read back to us using java reflection from the file
 * This data is stored to an array and than compared to the older data to see if it is infact the same after 
 * the serialization process
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/11/2014
 */

public class Driver {
    
    public static void main(String[] args) {
		
		//Error Checking for correct input: int > 0, String, int 0 - 4
			int numOfObjects = 0;

		try{
			if(Integer.parseInt(args[0]) <= 0){
				Logger.dump(2, "Crashed in Driver, Number of Objects needs to be greater than 0");
				System.exit(1);
			}
			else{
				numOfObjects = Integer.parseInt(args[0]);
			}
		} catch (NumberFormatException e){
			Logger.dump(1, "Crashed in Driver, Number of Objects needs to be a Number");
			System.exit(-1);
		}

		String checkpointFile = args[1];
		
		try{
			if (Integer.parseInt(args[2]) >= 0 && Integer.parseInt(args[2]) <= 4) {
				Logger.setLevel(Integer.parseInt(args[2]));	
			} else {
				Logger.dump(2, "Crashed in Driver, DEBUG_VALUE needs to be within 0-4");
				System.exit(1);
			}
		} catch(NumberFormatException e){
			Logger.dump(1, "Crashed in Driver, DEBUG_VALUE needs to be an Integer");
			System.exit(-1);
		}

		//Creating Dynamic Proxy
		ProxyCreator pc = new ProxyCreator();
		InvocationHandler handler = new StoreRestoreHandler();

		StoreRestoreI cpointRef = (StoreRestoreI) pc.createProxy(new Class[] {StoreI.class, RestoreI.class}, handler);

		
		//Open the file	for writing
		((StoreRestoreHandler)handler).openWriter(checkpointFile);

		//Serialization
		SerializableObject myErecord, mySrecord;
		SerializableObject[] myEArray = new SerializableObject[numOfObjects];
		SerializableObject[] mySArray = new SerializableObject[numOfObjects];


		for (int i = 0; i < numOfObjects; i++) {
		    myErecord = new EmployeeRecord(i);
		    ((EmployeeRecord) myErecord).set_float((float) (i + 3.5));
		    ((EmployeeRecord) myErecord).set_double((double) (i * 5.5));
		    ((EmployeeRecord) myErecord).set_long((long) (i * 10));

		    mySrecord = new StudentRecord(i);
		    ((StudentRecord) mySrecord).set_short((short) (i * 2));
		    ((StudentRecord) mySrecord).set_boolean((i % 2) > 0 ? true : false);
		 

		    myEArray[i] = myErecord;
		    mySArray[i] = mySrecord;
		    ((StoreI) cpointRef).writeDJSON(myErecord, "djson");
			((StoreI) cpointRef).writeDJSON(mySrecord, "djson");
		}

		// Close the file for writing
		((StoreRestoreHandler)handler).closeWriter();
		//Open the file	for reading
		((StoreRestoreHandler)handler).openReader(checkpointFile);

		//Deserialization
		SerializableObject[] myRArray = new SerializableObject[2 * numOfObjects];


		for (int i = 0; i < (2 * numOfObjects); i++) {
			myRArray[i] = ((RestoreI) cpointRef).readDJSON("djson");
		}

		// Close the file for reading

		((StoreRestoreHandler)handler).closeReader();

		//Comparison Code
		int e = 0;
		int s = 0; 
		int i = 0;
		while(i != numOfObjects){
			if(myRArray[i].equals(myEArray[e])){
				Logger.dump(0,"They are Equal");
				e++;
			} else if(myRArray[i].equals(mySArray[s]))	 {
				Logger.dump(0,"They are Equal");
				s++;
			} else{
				Logger.dump(0,"Not Equal");
			}
			i++;
	    }
	}
}
