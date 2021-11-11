package compresion;

import algoritmos.Huffman;
import algoritmos.RLC;
import algoritmos.ShannonFano;

public class Prueba {

	public static void main(String[] args) {
		System.out.println("Ejecutamo");
		
		RLC rlc= new RLC();
		rlc.compresionRLC("Argentina.txt");
		rlc.compresionRLC("Estonio.txt");
		rlc.compresionRLC("imagen.raw");
		
		ShannonFano sF = new ShannonFano();
		sF.compresionShannonFano("Argentina.txt");
		sF.compresionShannonFano("Estonio.txt");
		sF.compresionShannonFano("imagen.raw");
		
		Huffman Hm = new Huffman();
		Hm.compresionHuffman("Argentina.txt");
		Hm.compresionHuffman("Estonio.txt");
		Hm.compresionHuffman("imagen.raw");
		System.out.println("Salimos");
	}
}
