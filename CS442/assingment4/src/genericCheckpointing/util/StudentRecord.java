package genericCheckpointing.util;

import genericCheckpointing.util.Logger;

/**
 *
 * Serializable object that would eventually be used to see if serialization is done correctly
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/11/2014
 */

public class StudentRecord extends SerializableObject {

	private int i;
	private short s;
	private boolean b;
	
	/**
	 * Empty Constructor
	 */
	public StudentRecord() {
		Logger.dump(4, "Constructor called for StudentRecord");
	}

	/**
	 * Explict Constructor
	 *
	 * @param i		i value taken in from driver
	 */
	public StudentRecord(int i) {
		Logger.dump(4, "Constructor called for StudentRecord");
		this.i = i;
	}

	/**
	 * Getter for i
	 * 
	 * @return i	return the i from StudentRecord object
	 */
	public int get_int() {
		return i;
	}

	/**
	 * Setter for i
	 *
	 * @param i	   The i that is given from the file or initially from deserialization
	 */
	public void set_int(int i) {
		this.i = i;
	}

	/**
	 * Getter for s
	 * 
	 * @return s	return the s from StudentRecord object
	 */
	public short get_short() {
		return s;
	}

	/**
	 * Setter for s
	 *
	 * @param s	   The s that is given from the file or initially from deserialization
	 */
	public void set_short(short s) {
		this.s = s;
	}

	/**
	 * Getter for b
	 * 
	 * @return b	return the b from StudentRecord object
	 */
	public boolean get_boolean() {
		return b;
	}

	/**
	 * Setter for b
	 *
	 * @param b	   The b that is given from the file or initially from deserialization
	 */
	public void set_boolean(boolean b) {
		this.b = b;
	}
	
	/**
	 * hashCode
	 *
	 * The hashcode method needs to be overrided for our serialization to see if the value of our complex types are the same
	 */
	@Override
	public int hashCode() {
		final int prime = 113;
		int result = 1;
		result = prime * i;
		result = prime * (int) (result + s);
		if(b) {
			result++;
		}
		return result;
	}
 	
 	/**
	 * equals
	 *
	 * The equals method needs to be overrided for our serialization to see if the value of our complex types are the same
	 *
	 * @param obj 	This is the object you compare against to see if they are equal
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj){
			return true;
		}
		if (obj == null){
			return false;
		}
		if (getClass() != obj.getClass()){
			return false;
		}

		StudentRecord other = (StudentRecord) obj;
		if (i != other.get_int()){
			return false;
		}
		if (s != other.get_short()){
			return false;
		}
		if (b != other.get_boolean()){
			return false;
		}
		return true;
	}

	@Override
	public String toString(){
		return "StudentRecord: " + this.i + " " + this.s + " " + this.b + "\n";
	}

}
