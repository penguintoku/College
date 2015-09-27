package csRegs.util;

import csRegs.dataStore.StudentInfo;

import csRegs.interfaces.SexyCode;
import csRegs.interfaces.DataStorage;

import java.util.Vector;

/**
 *
 * The class will create a vector for the data where all the
 * infromaton of the student will be. 
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class RegistrationStore implements SexyCode, DataStorage {


	private	Vector<StudentInfo> data = new Vector<StudentInfo>();

	/**
	 * Empty Constructor
	 */
	public RegistrationStore(){
		Logger.dump(4,"Constructor for RegistrationStore called.");
	}


	/**
	 * Getter for data
	 *
	 * @return data 	Vector that holds all inputs from the dataFile 
	 */
	public Vector<StudentInfo> getData(){
		return data;
	}

	/**
	 * Setter for data
	 *
	 * @param data 		Vector that holds all inputs from the dataFile
	 */
	public void setData(Vector<StudentInfo> data){
		this.data = data;
	}

	/**
	 * displayData
	 *
	 * Prints out each element of StudentInfo in the Vector
	 */
	public void displayData(){
		for(int i = 0; i<data.size(); i++){
			System.out.println(data.get(i));
		}
	}
	
	@Override
	public String toString(){
		return "RegistrationStore: " + this.data + "\n";
	}
}
