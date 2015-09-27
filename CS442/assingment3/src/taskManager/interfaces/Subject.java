package taskManager.interfaces;

import taskManager.util.Filter;

import java.util.ArrayList;

/**
 *
 * Interface for the Subject
 * 
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */
public interface Subject {
  public void registerObserver(Observer o, Filter f);
  public void removeObserver(Observer o);
  public void notifyObservers(ArrayList<String> s);
}
