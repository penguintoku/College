package chat.util;

import chat.interfaces.SexyCode;
import chat.server.ServerThread;

import java.util.LinkedList;

/**
 *
 * Creates a thread pool where the threadpool size is 
 * depended inside the Server Driver
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/28/2014
 */


public class ThreadPool implements SexyCode {

	private static ThreadPool pool = null;
	private LinkedList<Runnable> queue;
	
	/**
	 * Creates a thread pool in a linked list form.
	 * 
	 * @param threadCount 		The size of the thread pool
	 */
	private ThreadPool(int threadCount) {
		
		queue = new LinkedList<Runnable>();
		
		for (int i = 0; i < threadCount; i++) {
			Runnable messenger = new ServerThread();
			Thread thread = new Thread(messenger);
			queue.add(thread);
		}
	}

	/**
	 *
	 * Checks to see if a thread pool already exists. 
	 * If not, create a thread pool with the desired
	 * thread pool amount. If already exists, use the
	 * the thread pool that exists.
	 *
	 * @return pool 	returns a newly made or existing thread pool 
	 */

	public synchronized static ThreadPool getInstance(int threadCount){

	 	if(pool == null){
	 		pool = new ThreadPool(threadCount);
	 	}
	 	return pool;
	 }

	// /**
	//  *
	//  * Checks to see if a thread pool already exists. 
	//  * If not, create a thread pool with the desired
	//  * thread pool amount. If already exists, use the
	//  * the thread pool that exists.
	//  *
	//  * @return pool 	returns a newly made or existing thread pool 
	//  */
	// public static ThreadPool getInstance(int threadCount){

	// 	synchronized (pool){
	// 		if (pool == null){
	// 			pool = new ThreadPool(threadCount);
	// 		}
	// 		return pool;
	// 	}
	// }


	/**
	 *
	 * Borrows a thread from a thread pool
	 *
	 * @return thread 		remove thread from pool
	 */
	public Thread borrowThread() {  
		return (Thread) queue.remove();    
	}

	/**
	 *
	 * Put back a thread that is no longer used into the pool
	 *
	 * @param thread 		returns a thread back the thread pool
	 */
	public void returnThread(Thread thread) {  
		queue.add(thread);    
	}
}