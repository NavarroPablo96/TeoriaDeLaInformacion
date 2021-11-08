package algoritmos;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;

public class RLC {
	/*if(nombreArchivo.contains(".raw")) {
		    System.out.println("Es .raw");
		    
		}
		if(nombreArchivo.contains(".txt")) {
		    System.out.println("Es .txt");
		}*/

	public void compresionRLC(String nombreArchivo) {
	    File archivo = null;
	    FileReader fr = null;
	    
	    FileWriter fichero = null;
        PrintWriter pw = null;

		try {
			archivo = new File (nombreArchivo);
	        fr = new FileReader (archivo);

	        fichero = new FileWriter(nombreArchivo +".RLC");
            pw = new PrintWriter(fichero);

			
			
			//cada algoritmo (input)
			int caracter = fr.read();
			char anterior = (char)caracter;
			int apariciones=1;
			
			
			while (caracter!=-1) {
				//System.out.println((char) caracter);
                //pw.println((char) caracter);
				caracter = fr.read();
				char actual  = (char) caracter;
				if(actual!='\n' && actual!='\0' && actual!=13) {
					if(anterior != actual) {
						pw.print(anterior);
						pw.println(apariciones);
						anterior=actual;
						apariciones=1;
					}
					else {
						apariciones++;
					}
				}
				else {
					//pw.println("caracter invisible " + (int)actual);
				}
            }
			fr.close();
			pw.close();
		}catch(Exception ex) {
			ex.printStackTrace();
		}
	}
	
	//parámetro 
	//1byte para el caracter		2bytes para numeros
	//if (archivo termina en ".raw")
	//leer los primeros 2 numeros y multiplicarlos
	// 256 x 256 = 65536 = 2^16, osea que se necesitan 2 bytes para almacenar el numero
	//	char ==('0','1','2','3','4','5','6','7')	long
	
	//6 1024 7 20
	
	public static void copia (String ficheroOriginal, String ficheroCopia)
	{
		try
		{
			// Se abre el fichero original para lectura
			FileInputStream fileInput = new FileInputStream(ficheroOriginal);
			BufferedInputStream bufferedInput = new BufferedInputStream(fileInput);
			
			// Se abre el fichero donde se hará la copia
			FileOutputStream fileOutput = new FileOutputStream (ficheroCopia);
			BufferedOutputStream bufferedOutput = new BufferedOutputStream(fileOutput);
			
			// Bucle para leer de un fichero y escribir en el otro.
			byte [] array = new byte[1000];
			int leidos = bufferedInput.read(array);
			while (leidos > 0)
			{
				bufferedOutput.write(array,0,leidos);
				leidos=bufferedInput.read(array);
			}

			// Cierre de los ficheros
			bufferedInput.close();
			bufferedOutput.close();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}