package compresion;

import java.io.File;
import java.util.Scanner;

import algoritmos.Huffman;
import algoritmos.RLC;
import algoritmos.ShannonFano;

public class Prueba {

	public static void main(String[] args) {
		//System.out.println("Ingrese nombre del archivo:");
		//Prueba p= new Prueba();
		System.out.println("Ejecutamo");
		
//		RLC rlc= new RLC();
//		rlc.compresionRLC("Argentina.txt");
//		rlc.compresionRLC("Estonio.txt");
//		rlc.compresionRLC("imagen.raw");
//		p.abrirArchivo("Estonio.txt");
//		p.abrirArchivo("imagen.raw");
		
		ShannonFano sF = new ShannonFano();
		sF.compresionShannonFano("Argentina.txt");
		sF.compresionShannonFano("Estonio.txt");
		sF.compresionShannonFano("imagen.raw");
		
//		Huffman Hm = new Huffman();
//		Hm.compresionHuffman("Argentina.txt");
//		Hm.compresionHuffman("Estonio.txt");
//		Hm.compresionHuffman("imagen.raw");
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
