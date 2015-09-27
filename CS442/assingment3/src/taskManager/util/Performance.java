package taskManager.util;

import taskManager.util.Logger;

import taskManager.interfaces.Subject;
import taskManager.interfaces.Observer;

import java.util.ArrayList;
import java.util.HashMap;
/**
 *
 * The Performance option of the tab which will
 * update the task of this tab from the file. This
 * will update the tab each time its shown.
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */
public class Performance implements Observer {

  private ArrayList<String> history;
  private ArrayList<HashMap<String, String>> data;

  /**
   * Empty Constructor
   */
  public Performance() {
    history = new ArrayList<String>();
    data = new ArrayList<HashMap<String, String>>();
    Logger.dump(4, "Empty Constructor in Performance.");
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
    Logger.dump(2, "Performance: update called.");
    boolean exists = false;
    for (HashMap<String, String> map : this.data) {
      if (!map.get("memoryUsage").equals(arg.get(1)) ||
          !map.get("cpuUsage").equals(arg.get(2))) {
        map.put("memoryUsage", arg.get(1));
        map.put("cpuUsage", arg.get(2));
        exists = true;
      }
      if (!exists) {
        HashMap<String, String> perf = new HashMap<String, String>();
        perf.put("memoryUsage", arg.get(1));
        perf.put("cpuUsage", arg.get(2));
        perf.put("physicalMemory", arg.get(3));
        perf.put("cached", arg.get(4));
        this.data.add(perf);
      }
    }
    String newLine = "Memory Usage:" + arg.get(1) + " " +
                     "CPU usage:" + arg.get(2) + " " +
                     "Total Physical Memory:" + arg.get(3) + " " +
                     "Total Cached:" + arg.get(4);
    history.add(newLine);
  }

  /**
   * prints the information to the user
   */
  @Override
  public void printLatest() {
    Logger.dump(1, "Performance: printLatest called.");
    for (HashMap<String, String> m : this.data) {
      String memUse = m.get("memoryUsage");
      String cpuUse = m.get("cpuUsage");
      String phyMem = m.get("physicalMemory");
      String cached = m.get("cached");
    }
    if (history.size() > 0) {
      for(String s : history) {
        System.out.println(s);
      }
    }
  }

  @Override
  public String toString(){
    return "Performance: " + this.history + " " + this.data + "\n";
  }
}
