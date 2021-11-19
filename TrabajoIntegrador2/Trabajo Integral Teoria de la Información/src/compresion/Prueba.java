package compresion;

import algoritmos.Huffman;
import algoritmos.RLC;
import algoritmos.ShannonFano;

public class Prueba {

	public static void main(String[] args) {
		
		RLC rlc= new RLC();
//		rlc.compresionRLC("Argentina.txt");
//		rlc.compresionRLC("Estonio.txt");
		rlc.compresionRLC("imagen.raw");
		
//		ShannonFano sF = new ShannonFano();
//		System.out.println("Argentina.txt:");
//		sF.compresionShannonFano("Argentina.txt");
//		System.out.println("Estonio.txt:");
//		sF.compresionShannonFano("Estonio.txt");
//		sF.compresionShannonFano("imagen.raw");
		
//		Huffman Hm = new Huffman();
//		System.out.println("Argentina.txt:");
//		Hm.compresionHuffman("Argentina.txt");
//		System.out.println("Estonio.txt:");
//		Hm.compresionHuffman("Estonio.txt");
//		Hm.compresionHuffman("imagen.raw");
	}
}
