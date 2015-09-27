package taskManager.util;

import taskManager.util.Logger;

import taskManager.interfaces.Observer;

import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * The Processes option of the tab which will
 * update the task of this tab from the file. This
 * will update the tab each time its shown.
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */
public class Processes implements Observer {

  private ArrayList<String> history;
  private ArrayList<HashMap<String, String>> data;

  /**
   * Empty Constructor
   */
  public Processes() {
    history = new ArrayList<String>();
    data = new ArrayList<HashMap<String, String>>();
    Logger.dump(4, "Empty Constructor in Processes.");
  }
  
  /**
   *
   * update method which will update the information
   * by taking in the infromation from the file and 
   * save it inside a Hashmap where it will act as a 
   * history for this tab.
   *
   * @param arg    the Arralist argument
   */
  @Override
  public void update(ArrayList<String> arg) {
    Logger.dump(2, "Proecesses: update called.");
    boolean exists = false;
    for (HashMap<String, String> map : this.data) {
      if (map.containsValue(arg.get(1)) && map.containsValue(arg.get(2))) {
        map.put("cpu", arg.get(3));
        map.put("memory", arg.get(4));
        map.put("description", arg.get(5));
        exists = true;
      }
    }
    if (!exists) {
      HashMap<String, String> process = new HashMap<String, String>();
      process.put("processName", arg.get(1));
      process.put("userName", arg.get(2));
      process.put("cpu", arg.get(3));
      process.put("memory", arg.get(4));
      process.put("description", arg.get(5));
      data.add(process);
    }
    String newLine = "Process Name: " + arg.get(1) + " " +
                     "User Name: " + arg.get(2) + " " +
                     "CPU: " + arg.get(3) + " " +
                     "Memory: " + arg.get(4) + " " +
                     "Description: " + arg.get(5);
    history.add(newLine);
  }

  /**
   * prints the information to the user
   */
  @Override
  public void printLatest() {
    Logger.dump(1, "Processes: printLatest called.");
    for (HashMap<String, String> m : this.data) {
      String pname = m.get("processName");
      String uname = m.get("userName");
      String cpu = m.get("cpu");
      String memory = m.get("memory");
      String description = m.get("description");
    }
    if (history.size() > 0) {
      for(String s : history) {
        System.out.println(s);
      }
    }
  }
}
