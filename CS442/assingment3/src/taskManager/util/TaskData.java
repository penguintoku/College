package taskManager.util;

import taskManager.util.Logger;

import taskManager.interfaces.Subject;
import taskManager.interfaces.Observer;

import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * The Taskdata which will add, remove, or notify
 * an observer. 
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */

public class TaskData implements Subject {

  //private ArrayList<Filter> filters;
  //private ArrayList<Observer> observers;
  private ArrayList<HashMap<String, Object>> observers;

  /**
   * Empty Constructor
   */
  public TaskData() {
    //observers = new ArrayList<Observer>();
    //filters = new ArrayList<Filter>();
    observers = new ArrayList<HashMap<String, Object>>();
    Logger.dump(4, "Empty Constructor in TaskData.");
  }

  /**
   * Will call the history corresponding to the tab option
   * the user chose.
   *
   * @param s     the user input string
   */
  public void printHistory(String s) {
    Logger.dump(3, "TaskData: printHistory called.");
    if(s.equals("p")) {
      Observer o = (Observer)observers.get(0).get("Observer");
      o.printLatest();
      //observers.get(0).get("Observer").printLatest();
    } else if(s.equals("u")) {
      Observer o = (Observer)observers.get(1).get("Observer");
      o.printLatest();
      //observers.get(1).get("Observer").printLatest();
    } else {
      Observer o = (Observer)observers.get(2).get("Observer");
      o.printLatest();
      //observers.get(2).get("Observer").printLatest();
    }
  }

  /**
   * Will add an observer
   *
   * @param o     the observer
   * @param f     the filter
   */
  @Override
  public void registerObserver(Observer o, Filter f) {
    Logger.dump(3, "TaskData: registerObserver called.");
    HashMap<String, Object> observer = new HashMap<String, Object>();
    observer.put("Observer", o);
    observer.put("Filter", f);
    observers.add(observer);
    //observers.add(o);
    //filters.add(f);
  }

  /**
   * Will remove an observer
   *
   * @param o     the observer
   */
  @Override
  public void removeObserver(Observer o) {
    Logger.dump(3, "TaskData: removeObserver called.");
    for (int i = 0; i < observers.size(); i++) {
      if (observers.get(i).containsValue(o)) {
        observers.remove(i);
      }
    }
    /*
    int i = observers.indexOf(o);
    if (i >= 0) {
      observers.remove(i);
      filters.remove(i);
    }
    */
  }

  /**
   * Will notify all the observers and checks if valid
   *
   * @param s     the arraylist that contains all the observer info
   */
  @Override
  public void notifyObservers(ArrayList<String> s) {
    Logger.dump(3, "TaskData: notifyObservers called.");
    for (int i = 0; i < observers.size(); i++) {
      Filter f = (Filter)observers.get(i).get("Filter");
      if (f.valid(s.get(0))) {
        Observer o = (Observer)observers.get(i).get("Observer");
        o.update(s);
        //observers.get(i).get("Observer").update(s);
      }
      /*
      if(filters.get(i).valid(s.get(0))) {
        observers.get(i).update(s);
      }
      */
    }
  }

  @Override
  public String toString(){
    return "TaskData: " + this.observers + "\n";
  }
}

