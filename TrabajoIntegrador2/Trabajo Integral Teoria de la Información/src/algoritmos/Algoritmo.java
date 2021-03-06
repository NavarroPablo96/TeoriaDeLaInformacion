package algoritmos;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Algoritmo {
	protected HashMap<Character,Simbolo> simbolos = null;
	
	public void agregarSimbolo(char caracter) {
		if(simbolos.containsKey(caracter)) {
			simbolos.get(caracter).incrementarApariciones();
		}
		else {
			Simbolo nuevo = new Simbolo(caracter);
			simbolos.put(caracter,nuevo);
		}
	}
	
	public ArrayList<Simbolo> compresion(String nombreArchivo) {
		System.out.println("Compresion");
		File archivo = null;
	    FileReader fr = null;
	    this.simbolos = new HashMap<Character,Simbolo>();
	    
		try {
			int totalSimbolos = 0;
			archivo = new File (nombreArchivo);
			fr = new FileReader (archivo);
			int caracter = fr.read();
			while (caracter!=-1) {
				totalSimbolos++;
				agregarSimbolo((char)caracter);
				caracter = fr.read();
			}
			
			if(totalSimbolos>0) {
				for(Simbolo s:simbolos.values()) {
					s.setProbabilidad(s.getApariciones()/(float)totalSimbolos);
				}
			}
			fr.close();
		}
		catch(Exception ex) {
			ex.printStackTrace();
		}

		ArrayList<Simbolo> listaOrdenada= new ArrayList<Simbolo>();
		for(Simbolo s:simbolos.values()) {
			listaOrdenada.add(s);
		}
		Collections.sort(listaOrdenada);
		
		return listaOrdenada;
	}
	
	public void generaArchivoComprimido(HashMap <Character,String> codificaciones,String nombreArchivo,String extension)
	{
		File archivoLectura = null;
	    FileReader fr = null;
	    FileOutputStream archivoSalida;
	    BufferedOutputStream fw;
	    
		try {
			archivoLectura = new File (nombreArchivo);
			fr = new FileReader (archivoLectura);
			
			archivoSalida = new FileOutputStream (nombreArchivo+extension);
			fw = new BufferedOutputStream(archivoSalida);
			System.out.println("genera Archivo");
			String archivoCodificado="",actual;
			int caracter = fr.read();
			while (caracter!=-1) {
				actual= codificaciones.get((char)caracter);
				archivoCodificado+=actual;
				caracter = fr.read();
			}
			byte [] vectorDeBytes;
			vectorDeBytes = new BigInteger(archivoCodificado,2).toByteArray();
			fw.write(vectorDeBytes);
			
			fw.close();
			fr.close();
		}
		catch(Exception ex) {
			ex.printStackTrace();
		}
	}
	
	public void calculaEntropia(ArrayList<Simbolo> L) {
		float suma = 0;
		
		for(int i = 0; i<L.size(); i++) {
			suma += L.get(i).getProbabilidad() * (Math.log10(L.get(i).getProbabilidad())/Math.log10(2)) * -1;
		}
		
		System.out.println("Entrop??a= " + suma);
	}
	
	public void calculaLongMedia(ArrayList<Simbolo> L) {
		float suma = 0;
		
		for(int i = 0; i<L.size(); i++) {
			suma += L.get(i).getProbabilidad() * L.get(i).getCodificacion().length();
		}
		
		System.out.println("Longitud Media= " + suma);
	}

}
