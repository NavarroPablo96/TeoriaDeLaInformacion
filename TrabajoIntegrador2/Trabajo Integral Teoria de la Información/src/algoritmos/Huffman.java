package algoritmos;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Huffman extends Algoritmo{
	
	
	
	
	public void compresionHuffman(String nombreArchivo) {
		algoritmoHuffman(super.compresion(nombreArchivo),nombreArchivo);
	}
	
	private void algoritmoHuffman(ArrayList<Simbolo>L,String nombreArchivo) {
		System.out.println("AlgoritmoHuffman");
		Simbolo s;
		recursivoHuffman(L,L.size()-1);
		System.out.println("Sale de recursivo");
		HashMap <Character,String> codificaciones= new HashMap<Character,String>();
		
		for(int i=0; i<L.size();i++) {	// cargamos el hashmap Codificaciones
			s= L.get(i);
			codificaciones.put(s.getCaracter(), s.getCodificacion());
		}
		generaArchivoComprimido(codificaciones,nombreArchivo,".Huf");
		System.out.println("\n\nPost Huffman:");
		for(int i=0 ; i<L.size(); i++) {// recorremos L, y le actualizamos su codificacion
			s= L.get(i);
			//String cod=codificaciones.get(s.getCaracter());
			//s.setCodificacion(cod);
			System.out.println(s.getCaracter()+" codi="+s.getCodificacion()+" prob="+s.getProbabilidad());	
		}
		
	}
	
	//El arrayList ya está ordenado
	private void recursivoHuffman(ArrayList<Simbolo>auxLista,int n) {
		Simbolo anteultimo,ultimo;
		if(n>1) {//mientras haya almenos 2 elementos en el arraylist entra
			ultimo = auxLista.get(n);
			anteultimo = auxLista.get(n-1);

			Simbolo nuevo = new Simbolo('<'); // cualquier caracter
			nuevo.setProbabilidad(ultimo.getProbabilidad() + anteultimo.getProbabilidad());
			
			auxLista.remove(ultimo);
			auxLista.remove(anteultimo);

			auxLista.add(nuevo);
			
			Collections.sort(auxLista);

			recursivoHuffman(auxLista,n-1);
			//Vuelta:--

			auxLista.remove(nuevo);
			ultimo.setCodificacion(nuevo.getCodificacion());
			ultimo.addCaracter('1');
			anteultimo.setCodificacion(nuevo.getCodificacion());
			anteultimo.addCaracter('0');
			auxLista.add(anteultimo);
			auxLista.add(ultimo);
			
		}
		else { //n==1
			auxLista.get(1).addCaracter('1');
			auxLista.get(0).addCaracter('0');
		}
	}
	
	
}
