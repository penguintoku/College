package chat.server;

import chat.interfaces.SexyCode;
import chat.util.Logger;
import chat.util.ThreadPool;

import java.net.ServerSocket;
import java.net.InetAddress;

import java.util.Vector;

import java.io.IOException;
import java.util.NoSuchElementException; 

/**
 * 
 * The main method to start the program for the server side.
 *
 * The server driver will automatically connect to a 
 * free port available and tell the size of the thread
 * pool to be created. Each thread will be taken from the
 * pool and connect from server and client.
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/28/2014
 */

public class ServerDriver implements SexyCode {

	/**
	 * 
	 * The main method to start the program for the server side.
	 *
	 * The server driver will automatically connect to a 
 	 * free port available and tell the size of the thread
 	 * pool to be created. Each thread will be taken from the
 	 * pool and connect from server and client. The host name
 	 * will automatically be retrieved and displayed.
	 *
	 * @exception IOException 	If no available ports were found
	 */

	public static void main(String args[]) {

		if(args.length > 0) {
			Logger.dump(0, "Usage: ./run.sh Server");
			System.exit(1);
		}
		
		Vector<String> buffer = new Vector<String>();

		try {
			//Will automatically connect to an available free port
			ServerSocket serverSocket = new ServerSocket(0);
			int localport = serverSocket.getLocalPort();

			//Getting the hostname
			InetAddress address = InetAddress.getLocalHost();
			String hostname = address.getHostName();

			//Display the current hostname and local port connected
			System.out.println("\nThe current local host: " + hostname);
			System.out.println("Using the port number: " + localport);

			//Create a thread pool of 5 threads
			ThreadPool pool = ThreadPool.getInstance(5);

			System.out.println("\nWaiting for the Client to connect and send message.");
			
			while (true) {
				try{
					//borrow threads from the threadpool
					Thread thread = pool.borrowThread();
					thread = new Thread( new ServerThread(serverSocket.accept(), buffer) );
					thread.start();
				} catch(NoSuchElementException e){
					Logger.dump(0, "There are no available threads.");
					break;
				}
			}
		} catch (IOException e) {
			Logger.dump(0, "There was no free available ports");
			System.exit(1);
		}
	}
}