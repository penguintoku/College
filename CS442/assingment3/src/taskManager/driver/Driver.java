package taskManager.driver;

import taskManager.util.TaskData;
import taskManager.util.Processes;
import taskManager.util.Users;
import taskManager.util.Performance;
import taskManager.util.Filter;
import taskManager.util.Parser;
import taskManager.util.Logger;

import taskManager.interfaces.Subject;
import taskManager.interfaces.Observer;

import java.io.File;
import java.util.ArrayList;
import java.io.BufferedReader;
/**
 *
 * The driver class which will start the program. 
 * It will read in a file and depended on the user 
 * input, it will go through the file and update the
 * terminal as if it's a TaskManager or Activity Monitor.
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */

public class Driver {

  public static void main(String[] args) {
    int logValue = Integer.parseInt(args[1]);
    if (logValue < 0 || logValue > 4) {
      System.out.println("Logger value must be between 0 and 4.");
      System.exit(1);
    }
    TaskData taskData = new TaskData();
    ArrayList<String> line;
    ArrayList<ArrayList<String>> lineList;
    File file = new File(args[0]);


    Parser fileParser = new Parser(file);

    Observer processes = new Processes();
    Observer users = new Users();
    Observer performance = new Performance();

    taskData.registerObserver(processes, new Filter("Process"));
    taskData.registerObserver(users, new Filter("User"));
    taskData.registerObserver(performance, new Filter("Performance"));

    line = fileParser.parseLine();
    System.out.println(line.size());
    lineList = fileParser.splitLine(line);
    String s;
    while (line.size() > 0) {
      s = fileParser.readInput();

      if (!s.isEmpty()) {
        for (ArrayList<String> list : lineList) {
          taskData.notifyObservers(list);
        }
        taskData.printHistory(s);
        line = fileParser.parseLine();
        lineList = fileParser.splitLine(line);
      }
    }
  }
}
