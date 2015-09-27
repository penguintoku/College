package sortedInsertVisitors.driver;

import sortedInsertVisitors.util.Elements;
import sortedInsertVisitors.util.FileProcessor;
import sortedInsertVisitors.util.MyArrayList;
import sortedInsertVisitors.util.MyVector;
import sortedInsertVisitors.util.SortedInsertVisitor;
import sortedInsertVisitors.util.SlowInsertVisitor;
import sortedInsertVisitors.util.Visitor;
import sortedInsertVisitors.util.Logger;

import java.util.Vector;
import java.util.ArrayList;

/**
 *
 * The Driver class that contain the main method which will
 * run the program. It'll get the file from the command line
 * and call the FileProcessor. It'll create the elements and 
 * the visitors which then visits the elements. It will display
 * both results. 
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public class Driver{
	
	public static void main (String[] args){

		try{
			if (Integer.parseInt(args[1]) >= 0 && Integer.parseInt(args[1]) <= 4) {
				Logger.setLevel(Integer.parseInt(args[1]));	
			} 
			else {
				Logger.dump(4, "ERROR: DEBUG_VALUE needs to be within 0-4");
				System.exit(1);
			}
		} catch(NumberFormatException e){
			Logger.dump(4, "ERROR: NumberFormatException, DEBUG_VALUE must be a number");
			System.exit(1);
		}

		//Getting the file from command line
		String fileName = args[0];

		//create the elements
		Elements arraylist = new MyArrayList();
		Elements vector = new MyVector();

		//create the visitors
		Visitor slow = new SlowInsertVisitor(fileName);
		Visitor sort = new SortedInsertVisitor(fileName);

		//call the visitor and display
		Logger.dump(0, "Displaying arraylist of SortedInsertVisitor");
		arraylist.accept(sort);
		arraylist.display();

		Logger.dump(0, "Displaying arraylist of SlowInsertVisitor");
		arraylist.accept(slow);
		arraylist.display();

		Logger.dump(0, "Displaying vector of SortedInsertVisitor");
		vector.accept(sort);
		vector.display();

		Logger.dump(0, "Displaying vector of SlowInsertVisitor");
		vector.accept(slow);
		vector.display();
	}
}