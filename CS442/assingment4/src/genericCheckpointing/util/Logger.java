package genericCheckpointing.util;

import java.io.PrintWriter;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * The Logger method is to display all the messages at once throughout
 * the code in order to see the process. By changing the level, 
 * you can see what was created during the process.
 * The level is corresponded to the assignment given. 
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/10/2014
 */

public class Logger {

	private static int level;
	private static String message;

	/**
	 * Empty Constructor
	 */
	public Logger(){
	}

	/**
	 * Explict Constructor
	 *
	 * @param level		Takes in the DEBUG_LEVEL from the driver
	 * @param message	Message is hardcoded in from each indivdual method call
	 */
	public Logger(int level, String message){
		this.level = level;
		this.message = message;
	}

	/**
	 * dump
	 *
	 * The method checks if the input level is the same as the original debug level
	 * from the driver and if so it prints out the message.
	 *
	 * @param inputLevel
	 * @param inputMessage
	 */
	public static void dump(int inputLevel, String inputMessage){
		if(level == inputLevel){
			System.out.println(inputMessage);
		}
	}

	/**
	 * toFile
	 *
	 * This method outputs data to a file
	 *
	 * @param inputMessage 	the StringBuffer
	 * @param writer		the PrintWriter
	 */
	public static void toFile(StringBuffer inputMessage, PrintWriter writer){
		writer.println(inputMessage);
	}

	/**
	 * Getter for level
	 *
	 * Will get level of the DEBUG_LEVEL
	 * 
	 * @return level	return the level of the debug
	 */
	public static int getLevel(){
		return level;
	}

	/**
	 * Getter for message
	 *
	 * Will get message corresponding to the hardcoded message
	 * 
	 * @return message	return the message of the debug
	 */
	public static String getMessage(){
		return message;
	}

	/**
	 * Setter for level
	 *
	 * @param level	   The level given by each corresponding dump
	 */
	public static void setLevel(int level){
		Logger.level = level;
	}

	/**
	 * Setter for message
	 *
	 * @param message The message given by each corresponding dump
	 */
	public static void setMessage(String message){
		Logger.message = message;
	}

	@Override
	public String toString(){
		return "Logger: " + this.level + " " + this.message + "\n";
	}
}
