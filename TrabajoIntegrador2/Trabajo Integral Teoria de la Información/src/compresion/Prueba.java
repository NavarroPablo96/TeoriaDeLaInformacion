package compresion;

import java.io.File;
import java.util.Scanner;

import algoritmos.RLC;

public class Prueba {

	public static void main(String[] args) {
		//System.out.println("Ingrese nombre del archivo:");
		//Prueba p= new Prueba();
		RLC.compresionRLC("Argentina.txt");
		RLC.compresionRLC("Estonio.txt");
		RLC.compresionRLC("imagen.raw");
		//p.abrirArchivo("Estonio.txt");
		//p.abrirArchivo("imagen.raw");
	}
	
	
	public void abrirArchivo(String nombre_archivo) {
		try {
			Scanner input = new Scanner((new File(nombre_archivo)));
			//cada algoritmo (input)
			while (input.hasNextLine()) {
                String line = input.nextLine();
                //int numero = input.nextInt();
                System.out.println(line);
                //System.out.println(numero);
			}
            input.close();
		}catch(Exception ex) {
			ex.printStackTrace();
		}
	}

}
