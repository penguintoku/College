package taskManager.interfaces;

import java.util.ArrayList;

/**
 *
 * Interface for the Observer
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */
public interface Observer {
  public void update(ArrayList<String> data);
  public void printLatest();
}
