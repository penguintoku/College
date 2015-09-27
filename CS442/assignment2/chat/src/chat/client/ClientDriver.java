package chat.client;

import chat.interfaces.SexyCode;
import chat.util.Logger;

import java.lang.Runnable;

import java.net.Socket;
import java.net.InetAddress;

import java.util.Vector;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;

import java.io.IOException;
import java.net.UnknownHostException;
import java.lang.NumberFormatException;
import java.lang.ArrayIndexOutOfBoundsException;

/**
 * 
 * The main method to start the program for the client side.
 *
 * The client driver will connect to the port for what the
 * user has entered. The host name will automatically be 
 * retrieved. Once a connection has been established with the server,
 * provides a message for the user to use. 
 *
 * @author MW
 * @author Tokumaru Yahashi
 * @version %I%, %G%
 * @since 2/28/2014
 */


public class ClientDriver implements SexyCode {

	/**
	 * 
	 * The main method to start the program for the client side.
	 *
	 * The client driver will connect to the port for what the
	 * user has entered. The host name will automatically be 
	 * retrieved. Once a connection has been established with the server,
	 * provides a message for the user to use. 
	 *
	 * @exception unknownHostException 				If no host was found
	 * @exception IOException 						Couldn't connect to server
	 * @exception NumberFormatException 			Couldn't find the port number
	 * @exception ArrayIndexOutOfBoundsException	Wasn't the right format to run
	 */

	public static void main(String args[]) {
		
		try{

			if(args.length > 1) {
				Logger.dump(0, "Usage: ./run.sh Client portNumber");
				System.exit(1);
			}
		
			String name = "Client";
			int portNumber = Integer.parseInt(args[0]);
			Vector<String> buffer = new Vector<String>();
			
			//Getting the hostname
			InetAddress address = InetAddress.getLocalHost();
			String hostname = address.getHostName();

			//Establishing a new socket
			Socket socket = new Socket(hostname, portNumber);

			//For user input and retrieving from server input
			BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			  
			//String fromServer= null;
			String fromUser = null;

			//Displaying the menu
			while(true){
				out.print("");
				if(out.checkError()){
						System.out.println("The server died");
						System.exit(0);
				}

				System.out.print("\n1. Give me a name\n" +
					"2. Send message to server\n" +
					"3. Print message from server\n" +
					"4. Quit\n\n" +
					"Please choice 1, 2, 3, 4, or BACKUP\n" +
					"Choice: ");
				fromUser = stdIn.readLine();

				if(fromUser.equals("1")){
					System.out.println("\nType the name you would like to be refrenced as:");
					name = stdIn.readLine();
					System.out.println("\nYour name has been changed to: " + name);
				}
				else if(fromUser.equals("2")){
					System.out.println("\nType your message you would like to send:");
					fromUser = stdIn.readLine();
					buffer.add(name + ": " + fromUser + "\n");
					out.println(name + ": " + fromUser);
					System.out.println("Your message has been sent to the server");
				}
				else if(fromUser.equals("3")){ 
					if(!buffer.isEmpty()){
						System.out.println("Server: " + in.readLine());
					}
					else{
						System.out.println("\nThe server has not recieved any messages at this time.");
					}
				}
				else if(fromUser.equals("4")){
					System.out.println("\nGood Bye, " + name + "!\n");
					System.exit(0);
				}
				else if(fromUser.equals("BACKUP")){
					out.println("BACKUP");
					int i = 0;
					try{
						while(!in.readLine().equals("BACKUP")){
							Logger.toFile(buffer.get(i));
							i++;
						}
						Logger.closeFile();
					} catch(NullPointerException e){
						Logger.dump(0, "Gone Wrong");
					}
				}
				else{
					System.out.println("Options 1~4, or BACKUP");
				}       
			}
		} catch (UnknownHostException e) {
			Logger.dump(0, "Couldn't retrieve the host name");
			System.exit(1);
		} catch (IOException e) {
			Logger.dump(0, "Couldn't get I/O for the connection");
			System.exit(1);
		} catch (NumberFormatException e) {
			Logger.dump(0, "Couldn't reference the port number");
			System.exit(1);
		} catch (ArrayIndexOutOfBoundsException e){
			Logger.dump(0, "Usuage: ./run.sh Client portNumber");
			System.exit(1);
		}
	}
	
}