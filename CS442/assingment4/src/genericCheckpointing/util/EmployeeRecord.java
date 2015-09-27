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

public class EmployeeRecord extends SerializableObject {
	private int i;
	private float f;
	private double d;
	private long l;
	
	/**
	 * Empty Constructor
	 */
	public EmployeeRecord() {
		Logger.dump(4, "Constructor called for EmployeeRecord");
	}

	/**
	 * Explict Constructor
	 *
	 * @param i		i value taken in from driver
	 */
	public EmployeeRecord(int i) {
		Logger.dump(4, "Constructor called for EmployeeRecord");
		this.i = i;
	}

	/**
	 * Getter for i
	 * 
	 * @return i	return the i from EmployeeRecord object
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
	 * Getter for f
	 * 
	 * @return f	return the f from EmployeeRecord object
	 */
	public float get_float() {
		return f;
	}

	/**
	 * Setter for f
	 *
	 * @param f	   The f that is given from the file or initially from deserialization
	 */
	public void set_float(float f) {
		this.f = f;
	}

	/**
	 * Getter for d
	 * 
	 * @return d	return the d from EmployeeRecord object
	 */
	public double get_double() {
		return d;
	}

	/**
	 * Setter for d
	 *
	 * @param d	   The d that is given from the file or initially from deserialization
	 */
	public void set_double(double d) {
		this.d = d;
	}

	/**
	 * Getter for l
	 * 
	 * @return l	return the l from EmployeeRecord object
	 */
	public long get_long() {
		return l;
	}

	/**
	 * Setter for l
	 *
	 * @param l	   The l that is given from the file or initially from deserialization
	 */
	public void set_long(long l) {
		this.l = l;
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
		result = prime * (int) (result + f);
		result = prime * (int) (result + d);
		result = prime * (int) (result + l);
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

		EmployeeRecord other = (EmployeeRecord) obj;
		if (i != other.get_int()){
			return false;
		}
		if (f != other.get_float()){
			return false;
		}
		if (d != other.get_double()){
			return false;
		}
		if (l != other.get_long()){
			return false;
		}
		return true;
	}

	@Override
	public String toString(){
		return "EmployeeRecord: " + this.i + " " + this.f + " " + this.d + " " + this.l + "\n";
	}

}
