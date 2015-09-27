package csRegs.util;

import csRegs.dataStore.StudentInfo;

import csRegs.interfaces.SexyCode;
import csRegs.interfaces.DataStorage;

import java.util.Vector;

/**
 * The class will create a vector for the search results. 
 * 
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class Results implements SexyCode, DataStorage  {

	private Vector<StudentInfo> results = new Vector<StudentInfo>();
	
	/**
	 * Empty Constructor
	 */
	public Results(){
		Logger.dump(4, "Constructor for Results called.");
	}
	
	/**
	 * Getter for results
	 *
	 * @return results 	the results of the search
	 */
	public Vector<StudentInfo> getData(){
		return results;
	}

	/**
	 * Setter for results
	 *
	 * @param data 		the vector of student inforomation
	 */
	public void setData(Vector<StudentInfo> data){
		this.results = data;
	}	

	@Override 
	public String toString(){
		Logger.dump(1, results.toString());
		return results.toString();
	}
}
