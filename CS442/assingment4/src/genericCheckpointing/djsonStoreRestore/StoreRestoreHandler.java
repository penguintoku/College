package genericCheckpointing.djsonStoreRestore;

import genericCheckpointing.util.Logger;
import genericCheckpointing.util.SerializableObject;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Field;
import java.lang.reflect.Type;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;

import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.FileWriter;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 *
 * This acts as the invocation handler for the dynamic proxy
 * The handler can get the print writer, open the file, and close the file
 * The handler can get the buffered reader, open the file, and close the file
 * The handler also has the invoke method which allows you to use your generic interfaces classes
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 4/11/2014
 */

public class StoreRestoreHandler implements InvocationHandler{
	
	private PrintWriter dataWriter;
	private BufferedReader dataReader;
	
	/**
	 * Empty Constructor
	 */
	public StoreRestoreHandler(){ 
		Logger.dump(4, "Constructor called for StoreRestoreHandler");
	}

	/**
	 * Getter for dataWriter
	 * 
	 * @return dataWriter	return the PrintWriter 
	 */
	public PrintWriter getDataWriter(){
		return dataWriter;
	}

	/**
	 * Getter for dataReader
	 * 
	 * @return dataReader	return the BufferedReader 
	 */
	public BufferedReader getDataReader(){
		return dataReader;
	}

	/**
	 * openWriter
	 * 
	 * This method opens the file to be read from
	 *
	 * @param dataFile	the name of the file to be opened
	 */
	public void openWriter(String dataFile){
		try{
			dataWriter = new PrintWriter(new BufferedWriter(new FileWriter(dataFile)));
		} catch(FileNotFoundException e){
			Logger.dump(1, "Crashed in StoreRestoreHandler, FileNotFoundException in the openWriter Method");
			System.exit(-1);
		} catch(IOException e){
			Logger.dump(1, "Crashed in StoreRestoreHandler, IOException in the openWriter Method");
			System.exit(-1);
		}	
	}

	/**
	 * openReader
	 * 
	 * This method opens the file to be read from
	 *
	 * @param dataFile	the name of the file to be opened
	 */
	public void openReader(String dataFile){
		try{		
			dataReader = new BufferedReader(new FileReader(new File(dataFile)));
		} catch(FileNotFoundException exception){
			Logger.dump(1, "Crashed in StoreRestoreHandler, FileNotFoundException in the openReader Method");
			System.exit(-1);
		}
	}

	/**
	 * closeWriter
	 *
	 * This method closes the print writer
	 *
	 */
	public void closeWriter(){
			dataWriter.close();
	}

	/**
	 * closeReader
	 * 
	 * This method closes the buffered reader
	 */
	public void closeReader (){
		try{		
			dataReader.close();
		} catch(IOException e){
			Logger.dump(1, "Crashed in StoreRestoreHandler, IOException in the closeReader Method");
			System.exit(-1);
		}	
	}

	/**
	 * invoke
	 * 
	 * This is the overriden invoke method for the invocation handler
	 * As it is a dynamic proxy this code simply chooses which method from the interfaces to invoke
	 *	
	 * @param proxy		The proxy passed into the invoke method 
	 * @param method 	The method that was called to invoke the proxy
	 * @param args 		The array of objects, arguments, that were passed in to that method call
	 * @return Object 	Object returned back from the invoke method
	 */
	@Override
	public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
		String name = method.getName();
		Logger.dump(3, "StoreRestoreHandler: Invoking " + name);

		Object retVal = null;
		
		//Serialize
		if(name.equals("writeDJSON")){
			StringBuffer sb = new StringBuffer();

			sb.append(args[0].getClass().getName() + " ");
			Field[] field = args[0].getClass().getDeclaredFields();
			for(int i =0; i < field.length; i++){
				try{
					field[i].setAccessible(true);
					sb.append(field[i].getType().getSimpleName() + " " + field[i].get(args[0]) + " ");
				} catch (IllegalArgumentException e){
					Logger.dump(1, "IllegalArgumentException in StoreRestoreHandler");
					System.exit(-1);
				} catch(IllegalAccessException e){
					Logger.dump(1, "IllegalAccessException in StoreRestoreHandler");
					System.exit(-1);
				}
			}
			Logger.toFile(sb, dataWriter);
			sb.delete(0, sb.length());
		}

		//Deserialize
		if(name.equals("readDJSON")){

			String[] line = dataReader.readLine().trim().split(" ");

			Class<?> cls = null;



			try {
				cls = Class.forName(line[0]);
			} catch (ClassNotFoundException e) {
				Logger.dump(1, "ClassNotFoundException in StoreRestoreHandler");
				System.exit(-1);
			}
			Constructor<?>[] constructors = null;
			try{
				constructors = cls.getDeclaredConstructors();
			} catch(SecurityException e){
				Logger.dump(1, "SecurityException in StoreRestoreHandler");
				System.exit(-1);
			}
			Constructor<?> constructor = null;
			for (int i = 0; i < constructors.length; i++) {
				constructor = constructors[i];
				if (constructor.getGenericParameterTypes().length == 0){
					break;
				}
			}
			try {
				constructor.setAccessible(true);
				retVal = constructor.newInstance();
			} catch (InstantiationException e){
				Logger.dump(1, "InstantiationException in StoreRestoreHandler");
				System.exit(-1);
			} catch (InvocationTargetException e){
				Logger.dump(1, "InvocationTargetException in StoreRestoreHandler");
				System.exit(-1);
			} catch(IllegalAccessException e){
				Logger.dump(1, "IllegalAccessException in StoreRestoreHandler");
				System.exit(-1);
			}

			for(int i = 1; i < line.length; i += 2) {

				String parameterType = line[i];
				String value = line[i + 1];
				Method[] allMethods = cls.getDeclaredMethods();
				for (Method m : allMethods) {
					String methodName = m.getName();
					if (methodName.equalsIgnoreCase("set_" + parameterType)) {
						try {
							Type[] type = m.getGenericParameterTypes();
							m.setAccessible(true);
							if(type[0] == short.class) {
								m.invoke(retVal, Short.parseShort(value));
							} else if(type[0] == int.class) {
								m.invoke(retVal, Integer.parseInt(value));
							} else if(type[0] == long.class) {
								m.invoke(retVal, Long.parseLong(value));
							} else if(type[0] == float.class) {
								m.invoke(retVal, Float.parseFloat(value));
							} else if(type[0] == double.class) {
								m.invoke(retVal, Double.parseDouble(value));
							} else if(type[0] == boolean.class) {
								m.invoke(retVal, Boolean.parseBoolean(value));
							}
						} catch (InvocationTargetException e){
							Logger.dump(1, "InvocationTargetException in StoreRestoreHandler");
							System.exit(-1);
						} catch(IllegalAccessException e){
							Logger.dump(1, "IllegalAccessException in StoreRestoreHandler");
							System.exit(-1);
						} catch(IllegalArgumentException e){
							Logger.dump(1, "IllegalArgumentException in StoreRestoreHandler");
							System.exit(-1);
						}
						break;
					}
				}
			}
		}

		return retVal;
	}

}