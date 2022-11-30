import java.io.*;
import java.net.*;

class TCPClient {

	public static void main(String argv[]) throws Exception {
		String sentence;
		String modifiedSentence;

		BufferedReader inFromUser = new BufferedReader(new InputStreamReader(
				System.in));

		int porta = 6789;
		String servidor = "localhost";

		System.out.println("Conectando ao servidor " + servidor + ":" + porta);

		Socket clientSocket = new Socket(servidor, porta);

		DataOutputStream outToServer = new DataOutputStream(clientSocket
				.getOutputStream());

		BufferedReader inFromServer = new BufferedReader(new InputStreamReader(
				clientSocket.getInputStream()));

		System.out.println("Digite string a ser enviada para o servidor");
		sentence = inFromUser.readLine();

		outToServer.writeBytes(sentence + '\n');

		modifiedSentence = inFromServer.readLine();

		System.out.println("Recebido do servidor: " + modifiedSentence);

		clientSocket.close();

	}
}
