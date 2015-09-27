package sortedInsertVisitors.util;

import sortedInsertVisitors.util.MyArrayList;
import sortedInsertVisitors.util.MyVector;

/**
 *
 * The Visitor Interface for the Visitor 
 * Required for the Visitor Pattern
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public interface Visitor{
	public void visit(MyArrayList array);
	public void visit(MyVector vector);
}