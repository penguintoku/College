package taskManager.util;

import taskManager.util.Logger;

/**
 *
 * The filter class which filters out to see if the 
 * string are valid or not.
 * 
 * @author SB
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/25/2014
 */

public class Filter {
  
  private String tag;
  
  /**
   * Empty Constructor
   */
  public Filter(){
		Logger.dump(4, "Empty Constructor in Filter.");
  }

  /**
   * Explicit Constructor
   * 
   * @param tagIn		the tag of the string input
   */
  public Filter(String tagIn) {
		this.tag = tagIn;
		Logger.dump(4, "Explicit Constructor in Filter.");
  }

  /**
   * Valid method which sees if the tag is valid.
   * 
   * @param tagIn		the tag to see if its valid
   * @return retVal		returns if tag is valid or not
   */
	public boolean valid(String tagIn) {
		boolean retVal = this.tag.equals(tagIn) ? true : false;
		return retVal;
	}

	@Override
	public String toString(){
		return "Filter: " + this.tag + "\n";
	}

}
