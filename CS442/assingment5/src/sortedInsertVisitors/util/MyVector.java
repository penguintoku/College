package sortedInsertVisitors.util;

import sortedInsertVisitors.util.Elements;
import sortedInsertVisitors.util.Visitor;
import sortedInsertVisitors.util.Logger;

import java.util.Vector;

/**
 *
 * The ArrayList which is one of the ADT that I used
 * for experimenting the Visitor Pattern.
 * It will make a new arraylist and display if called.
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public class MyVector implements Elements{

	private Vector<Integer> v;
	
	/**
	 * Empty Constructor
	 *
	 * makes a new vector
	 */
	public MyVector(){
		Logger.dump(1, "Empty Constructor called for MyVector");
		v = new Vector<Integer>();
	}

	/**
	 * Getter Method for the vector
	 * 
	 * @retrun v 	the vector
	 */
	public Vector<Integer> getVector(){
		return v;
	}

	/**
	 * Setter method for the vector
	 * 
	 * @param v 	the vector
	 */
	public void setVector(Vector<Integer> v){
		this.v = v;
	}

	/**
	 * Display's the elements inside the vector
	 */
	@Override
	public void display(){
		for(int i = 0; i < v.size(); i++){
			Logger.dump(0, Integer.toString(v.get(i)));
		}
	}

	/**
	 * The accept method which is required for the
	 * Visitor Pattern.
	 */
	@Override
	public void accept(Visitor visitor) {
		Logger.dump(2, "Accept method called in MyVector");
		visitor.visit(this);
	}

	@Override
	public String toString(){
		return "MyVector: " + this.v + "\n";
	}
}