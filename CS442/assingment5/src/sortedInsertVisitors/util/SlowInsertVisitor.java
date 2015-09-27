package sortedInsertVisitors.util;

import sortedInsertVisitors.util.FileProcessor;
import sortedInsertVisitors.util.MyArrayList;
import sortedInsertVisitors.util.MyVector;
import sortedInsertVisitors.util.Visitor;
import sortedInsertVisitors.util.Logger;

import java.util.Vector;
import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * One of the visitor which will insert the element
 * at the end of the ADTs and sort the list using
 * one of sorting library.
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public class SlowInsertVisitor implements Visitor{
	private int currentInt;
	private FileProcessor fp = new FileProcessor();
	private ArrayList<Integer> tempArray;
	private Vector<Integer> tempVector;
	private String fileName;
	/**
	 * The empty Constructor
	 *
	 */
	public SlowInsertVisitor(){
		Logger.dump(1, "Empty Constructor called for SlowInsertVisitor");
	}

	/**
	 * The Explicit Constructor
	 *
	 * @param fileName 		the file name
	 */
	public SlowInsertVisitor(String fileName){
		Logger.dump(1, "Explicit Constructor called for SlowInsertVisitor");
		this.fileName = fileName;
	}

	/**
	 * The visit method for the arraylist which
	 * gets the current integer and add it to the
	 * end of the arraylist and sort.
	 *
	 * @param arraylist 	the arraylist
	 */
	@Override
	public void visit(MyArrayList arraylist) {
		Logger.dump(3, "Visit method called for ArrayList in SlowInsertVisitor");

		//create a temporary arraylist
		tempArray = new ArrayList<Integer>();
		
		//opens the file and initialize
		fp.openReader(fileName);
		fp.initialize();

		for (int i = 0; i < fp.getSize(); i++) {
			currentInt = fp.nextInt();
			tempArray.add(currentInt);
			Collections.sort(tempArray);
		}

		//set the arraylist and close the reader
		((MyArrayList)arraylist).setArrayList(tempArray);
		fp.closeReader();
	}

	/**
	 * The visit method for the vector which
	 * gets the current integer and add it to the
	 * end of the vector and sort.
	 *
	 * @param vector 	the vector
	 */
	@Override
	public void visit(MyVector vector){
		Logger.dump(3, "Visit method called for Vector in SlowInsertVisitor");

		//create a temporary vector
		tempVector = new Vector<Integer>();

		//opens the file and initalize
		fp.openReader(fileName);
		fp.initialize();

		for (int i = 0; i < fp.getSize(); i++) {
			currentInt = fp.nextInt();
			tempVector.add(currentInt);
			Collections.sort(tempVector);
		}

		//set the vector and closes the reader
		((MyVector)vector).setVector(tempVector);
		fp.closeReader();
	}

	@Override
	public String toString(){
		return "SlowInsertVisitor: " + this.currentInt + " " + this.fp + " " + this.tempArray +
		 " " + this.tempVector + " " + this.fileName+ "\n";
	}

}