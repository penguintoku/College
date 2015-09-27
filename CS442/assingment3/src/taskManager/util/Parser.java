package taskManager.util;

import taskManager.util.Logger;

import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

import java.util.StringTokenizer;
import java.util.ArrayList;

/**
 *
 * The parser which will parse each line of the file and
 * gives options to the user for the tab. Depended on
 * the user input, the options will change.
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */
public class Parser {

  private File file;
  private BufferedReader reader;
  private BufferedReader inputReader;

  /**
   * Empty Constructor
   */
  public Parser(){
    Logger.dump(4, "Empty Constructor in Parser.");
  }

  /**
   * Explicit Constructor
   *
   * @param fileHandle    the file
   */
  public Parser(File fileHandle) {
    this.file = fileHandle;
    try {
      reader = new BufferedReader(new FileReader(this.file));
      inputReader = new BufferedReader(new InputStreamReader(System.in));
      Logger.dump(4, "Explicit Constructor in Parser.");
    } catch (FileNotFoundException e) {
      Logger.dump(0, "Could not find file.");
      System.exit(1);
    }
  }

  /**
   * The parseline method which will parse each line and
   * if the line is there, it'll add to the arraylist.
   *
   * @return retVal   the Arraylist
   */
  public ArrayList<String> parseLine() {

    ArrayList<String> retVal = new ArrayList<String>();
    String str = "";

    try {
      if ((str = this.reader.readLine()) != null) {
        StringTokenizer tokenizer = new StringTokenizer(str);
        while (tokenizer.hasMoreElements()) {
          retVal.add((String)tokenizer.nextElement());
        }
      }
    } catch (IOException e) {
      Logger.dump(0, "Could not read line.");
      System.exit(1);
    }
    return retVal;
  }
  
  /**
   * If there are more than 1 instruction in the same line,
   * will create a arraylist, and split so its possible to run.
   *
   * @return retList   returns the arraylist of other instructions
   */
  public ArrayList<ArrayList<String>> splitLine(ArrayList<String> str) {
    ArrayList<ArrayList<String>> retList = new ArrayList<ArrayList<String>>();
    for (int i = 0; i < str.size(); i++) {
      if (str.get(i).equals("Process")) {
        ArrayList<String> list = new ArrayList<String>();
        for (int j = 0; j < 6; j++) {
          list.add(str.get(i+j));
        }
        retList.add(list);
      }
      if (str.get(i).equals("Performance")) {
        ArrayList<String> list = new ArrayList<String>();
        for (int j = 0; j < 5; j++) {
          list.add(str.get(i+j));
        }
        retList.add(list);
      }
      if (str.get(i).equals("User")) {
        ArrayList<String> list = new ArrayList<String>();
        for (int j = 0; j < 3; j++) {
          list.add(str.get(i+j));
        }
        retList.add(list);
      }
    }
    return retList;
  }

  /**
   *
   * Displays the options for the user to choose from.
   * Reads in the user input and depending on the user input
   * it will control the monitor.
   * 
   * @return in     the letter option of the user input or blank.
   */

  public String readInput() {
    String in = "";
    System.out.println("Choose (p)rocesses, (u)sers, p(e)rformance, (q)uit: ");
    try {
      in = inputReader.readLine();
    } catch (IOException e) {
      Logger.dump(0, "Could not get user input.");
      System.exit(1);
    }
    if (in.equals("p") || in.equals("u") || in.equals("e")) {
      return in;
    } else if (in.equals("q")) {
      Logger.dump(0, "Quitting the program from user input.");
      System.exit(0);
    }
    return "";
  }

  @Override
  public String toString(){
    return "Parser: " + this.file + " " + this.reader + " " + this.inputReader + "\n";
  }
}
