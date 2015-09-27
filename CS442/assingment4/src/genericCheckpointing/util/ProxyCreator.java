package genericCheckpointing.util;

import genericCheckpointing.util.Logger;

import genericCheckpointing.server.StoreRestoreI;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;

/**
 *
 * This is a utility class used by the driver to create a dynamic proxy
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/11/2014
 */

public class ProxyCreator {

	/**
	 * Empty Constructor
	 */	
	public ProxyCreator(){
		Logger.dump(4, "Constructor called for ProxyCreator");
	}

	/**
	 * createProxy
	 *
	 * This method is used to create the dynamic proxy
	 *
	 * @param interfaceArray 		Any interface that is passed into the proxy, which it can access
	 * @param handler 				The invocationHanler passed in to the proxy
	 * @return storeRestoreRef 		New Proxy created
	 */
	public StoreRestoreI createProxy(Class<?>[] interfaceArray, InvocationHandler handler){
		StoreRestoreI storeRestoreRef = (StoreRestoreI) Proxy.newProxyInstance(getClass().getClassLoader(), interfaceArray, handler);
		return storeRestoreRef;
	}
	
}
