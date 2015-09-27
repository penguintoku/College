package sortedInsertVisitors.util;

import sortedInsertVisitors.util.Visitor;

/**
 *
 * The Visitor Interface for the Element 
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public interface Elements{
	public void accept(Visitor visitor);
	public void display();
}