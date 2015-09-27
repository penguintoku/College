package csRegs.interfaces;

import csRegs.dataStore.StudentInfo;

import java.util.Vector;

/**
 *
 * Interface for RegistrationStore and Reults Class
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/11/2014
 */

public interface DataStorage extends SexyCode {
	Vector<StudentInfo> getData();
	void setData(Vector<StudentInfo> data);
}