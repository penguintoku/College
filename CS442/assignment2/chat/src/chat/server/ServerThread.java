package chat.server;

import chat.interfaces.SexyCode;
import chat.util.Logger;

import java.lang.Runnable;

import java.net.ServerSocket;
import java.net.Socket;

import java.util.Vector;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;

import java.io.IOException;
import java.lang.NullPointerException;
 
/**
 *
 * After opening a socket, and a client opens to the server; once
 * there is a connection between server and client, the server will
 * display a menu where they can input what they wish. 
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 3/4/2014
 */

public class ServerThread implements SexyCode, Runnable {

	private Socket socket = null;
	private Vector<String> buffer;

	/**
	 * Empty Constructor
	 */
	public ServerThread() {
		Logger.dump(4, "Empty Constructor in ServerThread.");
	}

	/**
	 * Explict Constructor
	 *
	 * @param socket	that connection of the server
	 * @param buffer	for the user input buffer
	 */
	public ServerThread(Socket socket, Vector<String> buffer) {
		this.socket = socket;
		this.buffer = buffer;
		Logger.dump(4, "Explicit Constructor in ServerThread.");
	}

	/**
	 * Run
	 * 
	 * After successfully connecting, and a client is connected,
	 * will display a menu for the user. The user can choose what
	 * they would like to do. 
	 * 
	 * @exception IOException 	Will be thrown if there is an input/output error
	 */
	public void run() {
		try  { 
			BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			  
			String fromServer= null;
			String fromUser = null;

			while(true){
				//If the user types "BACKUP" will make a file of the messages
				if ((fromUser = in.readLine()).equals("BACKUP")){
					buffer.add("BACKUP");
					for(int i = 0; i < buffer.size(); i++){
						out.println(buffer.get(i));
					}
				}
				//put whatever the user input to the Server Buffer
				buffer.add(fromUser);

				//Displaying the option menu
				System.out.print("\n1. Send Message to all clients\n" +
					"2. Print message from client\n" +
					"3. Quit\n\n" + 
					"Please choice 1, 2, or 3\n" +
					"Choice: ");
				fromServer = stdIn.readLine();
				if(fromServer.equals("1")){   
					out.println(buffer.lastElement());
				}
				else if(fromServer.equals("2")){
					System.out.println(buffer.lastElement());
				}
				else if(fromServer.equals("3")){
					System.out.println("\nLeaving the program. Good Bye!\n");
					System.exit(0);
				}
				else{
					System.out.println("Options 1~3 Please");
				}
			}
		} catch (IOException e) {
			Logger.dump(0, "Client Exited by force quitting");
			System.exit(1);
		} catch (NullPointerException e) {
			Logger.dump(0, "Client Exited");
		} 
	}
}
