package genericCheckpointing.server;

import genericCheckpointing.util.Logger;

import genericCheckpointing.util.SerializableObject;

/**
 *
 * Interface that has the serialization method
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/10/2014
 */

public interface StoreI extends StoreRestoreI {
      void writeDJSON(SerializableObject aRecord, String wireFormat);
}