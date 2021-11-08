package compresion;

import java.io.File;
import java.util.Scanner;

import algoritmos.ShannonFano;

public class Prueba {

	public static void main(String[] args) {
		//System.out.println("Ingrese nombre del archivo:");
		//Prueba p= new Prueba();
		/*RLC rlc= new RLC();
		rlc.compresionRLC("Argentina.txt");
		rlc.compresionRLC("Estonio.txt");
		rlc.compresionRLC("imagen.raw");*/
		//p.abrirArchivo("Estonio.txt");
		//p.abrirArchivo("imagen.raw");
		System.out.println("Ejecutamo");
		ShannonFano sF = new ShannonFano();
		sF.compresionShannonFano("Argentina.txt");

		System.out.println("Salimo");
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
