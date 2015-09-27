package csRegs.dataStore;

import csRegs.util.Logger;

import csRegs.interfaces.SexyCode;

/**
 *
 * The template of how each student infromation will look like.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public class StudentInfo implements SexyCode {

	private String firstName;
	private String lastName;
	private String instructorName;
	private int courseNumber;

	/**
	 * Empty Constructor 
	 */	
	public StudentInfo(){
		Logger.dump(4,"Constructor for StudentInfo called.");
	}

	/**
	 * 
	 * Explicit Constructor 
	 *
	 * @param firstName			The first name of the student		
	 * @param lastName			The last name of the student
	 * @param instructorName 	The instructor name
	 * @param courseNumber		The course number
	 */

	public StudentInfo(String firstName, String lastName, String instructorName, int courseNumber){
		this.firstName = firstName;
		this.lastName = lastName;
		this.instructorName = instructorName;
		this.courseNumber = courseNumber;
		Logger.dump(4,"Constructor for StudentInfo called.");
	}

	/**
	 * Getter for the first name
	 *
	 * @return firstname 	returns the students first name
	 */
	public String getFirstName(){
		return firstName;
	}

	/**
	 * Getter for the last name
	 *
	 * @return lastname 	returns the students last name
	 */
	public String getLastName(){
		return lastName;
	}

	/**
	 * Getter for the instructor name
	 *
	 * @return instructorName 	returns the instructor's name
	 */
	public String getInstructorName(){
		return instructorName;
	}

	/**
	 * Getter for the course numeber
	 *
	 * @return courseNumber 	returns the course number
	 */
	public int getCourseNumber(){
		return courseNumber;
	}

	/**
	 * Setter for the first name
	 *
	 * @param firstName 	sets the first name
	 */	
	public void setFirstName(String firstName){
		this.firstName = firstName;
	}

	/**
	 * Setter for the last name
	 *
	 * @param lastName 	sets the last name
	 */		
	public void setLastName(String lastName){
		this.lastName = lastName;
	}

	/**
	 * Setter for the instructor name
	 *
	 * @param instructorName 	sets the instructor's name
	 */
	 	public void setInstructorName(String instructorName){
		this.instructorName = instructorName;
	}

	/**
	 * Setter for the course number
	 *
	 * @param courseNumber 	sets the course number
	 */	
	public void setCourseNumber(int courseNumber){
		this.courseNumber =  courseNumber;
	}

	@Override
	public String toString(){
		return this.firstName + " " + this.lastName + " " + this.instructorName + " " + this.courseNumber + "\n";
	}
}
