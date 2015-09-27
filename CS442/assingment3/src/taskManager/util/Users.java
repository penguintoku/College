package taskManager.util;

import java.util.ArrayList;
import java.util.HashMap;

import taskManager.util.Logger;
import taskManager.interfaces.Observer;

/**
 *
 * The Users option of the tab which will
 * update the task of this tab from the file. This
 * will update the tab each time its shown.
 *
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */

public class Users implements Observer {

	private ArrayList<String> history;
	private ArrayList<HashMap<String, String>> data;

	/**
	 * Empty Constructor
	 */
	public Users() {
		history = new ArrayList<String>();
		data = new ArrayList<HashMap<String, String>>();
		Logger.dump(4, "Empty Constructor in User.");
	}

	/**
	 *
	 * update method which will update the information
	 * by taking in the infromation from the file and 
	 * save it inside a Hashmap where it will act as a 
	 * history for this tab.
	 *
	 * @param arg		 the Arralist argument
	 */
	@Override
	public void update(ArrayList<String> arg) {
		Logger.dump(2, "Users: update called.");
		boolean exists = false;
		for (HashMap<String,String> map : this.data) {
			if (map.containsValue(arg.get(1))) {
				map.put("status", arg.get(2));
				exists = true;
			}
		}
		if (!exists) {
			HashMap<String,String> user = new HashMap<String, String>();
			user.put("userName", arg.get(1));
			user.put("status", arg.get(2));
			data.add(user);
		}
		String newLine = "User Name:" + arg.get(1) + " status:" + arg.get(2);
		history.add(newLine);
	}

	/**
	 * prints the information to the user
	 */
	@Override
	public void printLatest() {
		Logger.dump(1, "Users: printLatest called.");
		for (HashMap<String, String> m : this.data) {
			String un = m.get("userName");
			String s = m.get("status");
			System.out.println("User Name: " + un + " " +
								"Status: " + s);
		}
	}

	@Override
	public String toString(){
		return "User: " + this.history + " " + this.data + "\n";
	}
}