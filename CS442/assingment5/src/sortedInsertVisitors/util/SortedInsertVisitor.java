package sortedInsertVisitors.util;

import sortedInsertVisitors.util.FileProcessor;
import sortedInsertVisitors.util.MyArrayList;
import sortedInsertVisitors.util.MyVector;
import sortedInsertVisitors.util.Visitor;
import sortedInsertVisitors.util.Logger;

import java.util.ArrayList;
import java.util.Vector;

/**
 *
 * One of the visitor which will insert the element
 * at the correct place of the ADTs by inserting the 
 * sorted list.
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public class SortedInsertVisitor implements Visitor{

	private int currentInt;
	private FileProcessor fp = new FileProcessor();
	private ArrayList<Integer> tempArray;
	private Vector<Integer> tempVector;
	private String fileName;

	/**
	 * The empty Constructor
	 *
	 */
	public SortedInsertVisitor(){
		Logger.dump(1, "Empty Constructor called for SortedInsertVisitor");
	}

	/**
	 * The Explicit Constructor
	 *
	 * @param fileName 		the file name
	 */
	public SortedInsertVisitor(String fileName){
		Logger.dump(1, "Explicit Constructor called for SortedInsertVisitor");
		this.fileName = fileName;
	}

	/**
	 * The visit method for the arraylist which
	 * gets the current integer and add it to the
	 * correct place of the list
	 *
	 * @param arraylist 	the arraylist
	 */
	@Override
	public void visit(MyArrayList arraylist){
		Logger.dump(3, "Visit method called for ArrayList in SortedInsertVisitor");

		//create a temporary arraylist
		tempArray = new ArrayList<Integer>();

		//open the file and initilize
		fp.openReader(fileName);
		fp.initialize();

		//getting the first element and adding to the arraylist
		currentInt = fp.nextInt();
		tempArray.add(currentInt);

		//How many times it would loop
		for(int i = 0; i < fp.getSize()-1; i++){
			currentInt = fp.nextInt();
			
			//going through each element to check where to be placed
			for(int j = 0; j < fp.getSize(); j++){
				//found the location in the middle
				try{
					if(currentInt < tempArray.get(j)){
						tempArray.add(j, currentInt);
						break;
					}
					//iff the currentInt is the largest in the arraylist
					if((currentInt > tempArray.get(j)) && (j+1 == tempArray.size())){
						tempArray.add(currentInt);
						break;
					}
				} catch (IndexOutOfBoundsException e){
					Logger.dump(4, "ERROR: IndexOutOfBoundsException, Can't retrieve number");
					System.exit(1);
				}
			}
		}
		//set the arraylist and close the reader
		((MyArrayList)arraylist).setArrayList(tempArray);
		fp.closeReader();
	}

	/**
	 * The visit method for the vector which
	 * gets the current integer and add it to the
	 * correct place of the list
	 *
	 * @param vector 	the vector
	 */
	@Override
	public void visit(MyVector vector){
		Logger.dump(3, "Visit method called for Vector in SortedInsertVisitor");

		//create a temporary vector
		tempVector = new Vector<Integer>();
	
		//opent the file and itialize
		fp.openReader(fileName);
		fp.initialize();

		//getting the first element and adding to the vector
		currentInt = fp.nextInt();
		tempVector.add(currentInt);

		//How many times it would loop
		for(int i = 0; i < fp.getSize()-1; i++){
			currentInt = fp.nextInt();
			
			//going through each element to check where to be placed
			for(int j = 0; j < fp.getSize(); j++){
				try{
					//found the location in the middle
					if(currentInt < tempVector.get(j)){
						tempVector.add(j, currentInt);
						break;
					}
					//iff the currentInt is the largest in the vector
					if((currentInt > tempVector.get(j)) && (j+1 == tempVector.size())){
						tempVector.add(currentInt);
						break;
					}
				} catch (IndexOutOfBoundsException e){
					Logger.dump(4, "ERROR: IndexOutOfBoundsException, Can't retrieve number");
					System.exit(1);
				}	
			}
		}
		//set the vector and close the reader
		((MyVector)vector).setVector(tempVector);
		fp.closeReader();
	}

	@Override
	public String toString(){
		return "SortedInsertVisitor: " + this.currentInt + " " + this.fp + " " + this.tempArray +
		 " " + this.tempVector + " " + this.fileName+ "\n";
	}

}