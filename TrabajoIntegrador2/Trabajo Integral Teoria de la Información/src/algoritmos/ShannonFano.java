package algoritmos;

import java.util.ArrayList;
import java.util.HashMap;

public class ShannonFano extends Algoritmo{
	
	public void compresionShannonFano(String nombreArchivo) {
		ArrayList<Simbolo> listaOrdenada = super.compresion(nombreArchivo);
		
		algoritmoShannonFano(listaOrdenada,0,listaOrdenada.size());
		super.calculaEntropia(listaOrdenada);
		super.calculaLongMedia(listaOrdenada);
		HashMap <Character,String> codificaciones= new HashMap<Character,String>();
		Simbolo s;	
		for(int i=0; i<listaOrdenada.size();i++) {	// cargamos el hashmap Codificaciones
			s= listaOrdenada.get(i);
			codificaciones.put(s.getCaracter(), s.getCodificacion());
		}
		
		generaArchivoComprimido(codificaciones,nombreArchivo,".Fan");
		//Mostramos las codificaciones:
//		System.out.println("PostShannonFano:");
//		for(int i=0; i<listaOrdenada.size();i++) {
//			s= listaOrdenada.get(i);
//			System.out.println(s.getCaracter()+"   \tCod="+codificaciones.get(s.getCaracter()));	
//		}
	}
	
	private void algoritmoShannonFano(ArrayList<Simbolo>L, int limInf, int limSup) {
		int i;
		float totProb=0,probAcum=0;
		if(limInf != (limSup-1)) {
	        for(i=limInf; i<limSup; i++) {
	            totProb+= L.get(i).getProbabilidad();
	        }
	        i = limInf;
	        while(probAcum < (totProb/2)){
	            probAcum+= L.get(i).getProbabilidad();
	            L.get(i).addCaracter('1');
	            i++;
	        }
	        algoritmoShannonFano(L,limInf,i);
	        int j = i;
	        while(probAcum < totProb){
	            probAcum += L.get(j).getProbabilidad();
	            L.get(j).addCaracter('0');
	            j++;
	        }
	        algoritmoShannonFano(L,i,limSup);
		}
	}
}
