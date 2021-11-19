package algoritmos;


import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class RLC {

	public void compresionRLC(String nombreArchivo) {
	    File archivo = null;
	    FileReader fr = null;
	    
	    FileWriter fichero = null;
        PrintWriter pw = null;
        
        HashMap<String, Simbolo>L = new HashMap<String, Simbolo>();

		try {
			archivo = new File (nombreArchivo);
	        fr = new FileReader (archivo);

	        fichero = new FileWriter(nombreArchivo +".RLC");
            pw = new PrintWriter(fichero);

			int caracter = fr.read();
			char anterior = (char)caracter;
			int apariciones=1;
			int cantidad = 0;
			
			while (caracter!=-1) {
				caracter = fr.read();
				char actual  = (char) caracter;
				if(actual!='\n' && actual!='\0' && actual!=13) {
					if(anterior != actual) {
						insertaSimbolo(anterior+Integer.toString(apariciones),L);
						pw.print(anterior);
						pw.println(apariciones);
						cantidad++;
						anterior=actual;
						apariciones=1;
					}
					else {
						apariciones++;
					}
				}
//				else {
//					//pw.println("caracter invisible " + (int)actual);
//				}
            }
			if(cantidad>0) {
				for(Simbolo s:L.values()) {
					s.setProbabilidad(s.getApariciones()/(float)cantidad);
				}
			}
			calculaEntropia(L);
			calculaLongMedia(L);
			fr.close();
			pw.close();
		}catch(Exception ex) {
			ex.printStackTrace();
		}
	}
	
	public void insertaSimbolo(String cadena, HashMap<String, Simbolo> L) {
		if(L.containsKey(cadena)) {
			L.get(cadena).incrementarApariciones();
		}
		else {
			Simbolo nuevo = new Simbolo(cadena);
			L.put(cadena,nuevo);
		}
	}
	
	public void calculaEntropia(HashMap<String, Simbolo> L) {
		float suma = 0;
		
		for(Simbolo s:L.values()) {
			suma += s.getProbabilidad() * (Math.log10(s.getProbabilidad())/Math.log10(2)) * -1;
		}
		
		System.out.println("Entropía= " + suma);
	}
	
	public void calculaLongMedia(HashMap<String, Simbolo> L) {
		float suma = 0;
		
		for(Simbolo s:L.values()) {
			//System.out.println(s.getApariciones() + " - " + s.getCodificacion().length() + " - " + s.getProbabilidad() + " - " + s.getCodificacion());
			suma += s.getProbabilidad() * (s.getCodificacion().length() * 8);
		}
		
		System.out.println("Longitud Media= " + suma);
	}
}