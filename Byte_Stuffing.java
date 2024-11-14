// Java code for Byte_Stuffing Receiver 
package byte_stuffing; 
import java.io.*; 
import java.net.*; 

public class Byte_Stuffing { 
	public static void main(String[] args) throws IOException 
	{ 
		// Opens a socket for connection 
		ServerSocket servsock = new ServerSocket(45678); 

		// Used to block until a client connects to the server 
		Socket socket = servsock.accept(); 

		// Declaring I/O Streams 
		DataInputStream dis = new DataInputStream(socket.getInputStream()); 
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream()); 

		while (true) { 
			String out = new String(); 
			// Used to read the data sent by client 
			String res = dis.readUTF(); 
			System.out.println("Message Received...Successfully!!!"); 
			System.out.println("The Stuffed Message is : " + res); 

			for (int i = 1; i < res.length() - 1; i++) { 

			// If data contains a 'D' or 'F' do not unstuff it 
				if (res.charAt(i) == 'D' || res.charAt(i) == 'F') 
					out = out + res.charAt(i); 

				// If data contains 'E' followed by 'E', de-stuff the former 'E' 
				else if (res.charAt(i) == 'E' && res.charAt(i + 1) == 'E') { 
					out = out + 'E'; 
					i++; 
				} 
			} 
			System.out.println("The Destuffed Message is : " + out); 
			dos.writeUTF("success"); 
			String ch = dis.readUTF(); 
			if (ch.equals("bye")) { 
				System.out.println("Messaging is over.....EXITING"); 
				break; 
			} 
		} 

		// Closing all connections 
		socket.close(); 
		dis.close(); 
		dos.close(); 
	} 
} 
