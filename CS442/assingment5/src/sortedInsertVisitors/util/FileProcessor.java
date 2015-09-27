package sortedInsertVisitors.util;

import sortedInsertVisitors.util.Logger;

import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

import java.util.ArrayList;

/**
 *
 * The FileProcessor which will read in a file as an argument
 * and check if the file is valid. If the file is valid, it
 * will read each line of the file. The nextInt will display the 
 * current number in the file that is being read.
 *
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/18/2014
 */

public class FileProcessor{

	private BufferedReader dataReader;
	private int size;
	private ArrayList<Integer> arrayList;
	private int iterator;
	private int currentInt;
	private File dataFile;

	/**
	 * Empty Constructor
	 *
	 * restarts the iterator to 0
	 */
	public FileProcessor(){
		Logger.dump(1, "Empty Constructor called for FileProcessor");
	}

	/**
	 * openReader
	 * 
	 * This method opens the file to be read from
	 *
	 * @param dataFile	the name of the file to be opened
	 */
	public void openReader(String dataFile){
		try{
			dataReader = new BufferedReader(new FileReader(new File(dataFile)));
		} catch(FileNotFoundException e){
			Logger.dump(4, "ERROR: FileNotFoundException, could not reference the file");
			System.exit(1);
		}
	}

	/**
	 * closeReader
	 * 
	 * This method closes the buffered reader
	 */
	public void closeReader(){
		try{		
			dataReader.close();
		} catch(IOException e){
			Logger.dump(4, "ERROR: IOException, could not close file");
			System.exit(1);
		}	
	}

	/**
	 * The initialize method which will read each line
	 * of the file until the end and put each value to the arraylist
	 * and increment the size.
	 *
	 */
	public void initialize(){
		iterator = 0;
		size = 0;
		arrayList = new ArrayList<Integer>();
		String str = "";
		try {
			while ((str = this.dataReader.readLine()) != null){
				currentInt = Integer.parseInt(str);
				arrayList.add(currentInt);
				size++;
			}
		} catch (IOException e) {
			Logger.dump(4, "ERROR: IOException, could not read file");
			System.exit(1);
		} catch (NumberFormatException e) {
			Logger.dump(4, "ERROR: NumberFormatException, could not convert to number");
			System.exit(1);
		}

	}

	/**
	 * returns the size of the array size
	 *
	 * @return size 		the size
	 */
	public int getSize(){
		return size;
	}

	/**
	 * displays the integer one by one
	 *
	 * @return currentInt 	the current int
	 */
	public int nextInt(){			
		try{
			currentInt = arrayList.get(iterator);
			iterator++;
		} catch (IndexOutOfBoundsException e){
			Logger.dump(4, "ERROR: IndexOutOfBoundsException, could not get element");
			System.exit(1);
		}
		return currentInt;
	}

	@Override
	public String toString(){
		return "FileProcessor: " + this.dataReader + " " + this.size + " " + this.arrayList + " " + this.iterator +
		 " " + this.currentInt + " " + this.dataFile + "\n";
	}

}