package primera_parte;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Prueba {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		File archivo = new File ("C:\\datos para tp1.txt");
		FileReader fr=null;
		
		try {
			fr = new FileReader (archivo);
			
		}
		catch(FileNotFoundException e) {
			System.out.println("No existe el archivo");
		}
		
		BufferedReader br = new BufferedReader(fr);
		try {
		//String linea = br.readLine();
		
			br.read();
		}
		catch (IOException e) {
			
		}
	}

}
