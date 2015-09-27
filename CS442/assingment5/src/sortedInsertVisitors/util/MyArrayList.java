package sortedInsertVisitors.util;

import sortedInsertVisitors.util.Elements;
import sortedInsertVisitors.util.Visitor;
import sortedInsertVisitors.util.Logger;

import java.util.ArrayList;

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

public class MyArrayList implements Elements{

	private ArrayList<Integer> al;

	/**
	 * Empty Constructor
	 *
	 * makes a new ArrayList
	 */
	public MyArrayList(){
		Logger.dump(1, "Empty Constructor called for MyArrayList");
		al = new ArrayList<Integer>();
	}

	/**
	 * Getter Method for the arraylist
	 * 
	 * @retrun al 	the arraylist
	 */
	public ArrayList<Integer> getArrayList(){
		return al;
	}

	/**
	 * Setter method for the arraylist
	 * 
	 * @param al 	the arraylist
	 */
	public void setArrayList(ArrayList<Integer> al){
		this.al = al;
	}

	/**
	 * Display's the elements inside the arraylist
	 */
	@Override
	public void display(){
		for(int i = 0; i < al.size(); i++){
			Logger.dump(0, Integer.toString(al.get(i)));
		}
	}

	/**
	 * The accept method which is required for the
	 * Visitor Pattern.
	 */
	@Override
	public void accept(Visitor visitor) {
		Logger.dump(2, "Accept method called in MyArrayList");
		visitor.visit(this);
	}

	@Override
	public String toString(){
		return "MyArrayList: " + this.al + "\n";
	}
}