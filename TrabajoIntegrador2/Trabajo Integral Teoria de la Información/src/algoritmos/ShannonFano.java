package algoritmos;

import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class ShannonFano {
	
	private HashMap<Character,Simbolo> simbolos = new HashMap<Character,Simbolo>();
	//private TreeSet<Simbolo> simbolos = new TreeSet<Simbolo>();
	
	public void compresionShannonFano(String nombreArchivo) {
		File archivo = null;
	    FileReader fr = null;
	    
		try {
			int totalSimbolos = 0;
			archivo = new File (nombreArchivo);
			fr = new FileReader (archivo);
			int caracter = fr.read();
			System.out.println("A VER");
			while (caracter!=-1) {
				totalSimbolos++;
				agregarSimbolo((char)caracter);
				//System.out.println((char)caracter);
				caracter = fr.read();
			}
			
			if(totalSimbolos>0) {
				for(Simbolo s:simbolos.values()) {
					s.setProbabilidad(s.getApariciones()/(float)totalSimbolos);
				}
			}
			System.out.println("Total="+totalSimbolos);
			fr.close();
		}
		catch(Exception ex) {
			ex.printStackTrace();
		}

		
		ArrayList<Simbolo> listaOrdenada= new ArrayList<Simbolo>();
		for(Simbolo s:simbolos.values()) {
			listaOrdenada.add(s);
			//System.out.println(s.getCaracter()+" "+ s.getApariciones()+" prob="+s.getProbabilidad());
		}
		Collections.sort(listaOrdenada);
		System.out.println("Ordenada:");
		
		for(int i=0 ; i<listaOrdenada.size(); i++) {
			Simbolo s= listaOrdenada.get(i);
			System.out.println(s.getCaracter()+" "+ s.getApariciones()+" prob="+s.getProbabilidad());	
		}
		
		/*algoritmoShannonFano(listaOrdenada,0,listaOrdenada.size());
		System.out.println("PostShannonFano:");
		for(int i=0 ; i<listaOrdenada.size(); i++) {
			Simbolo s= listaOrdenada.get(i);
			System.out.println(s.getCaracter()+" "+ s.getApariciones()+" prob="+s.getProbabilidad()+ "   \tCod="+s.getCodificacion());	
		}*/
		algoritmoHuffman(listaOrdenada);
	}
	
	public void agregarSimbolo(char caracter) {
		if(simbolos.containsKey(caracter)) {
			simbolos.get(caracter).incrementarApariciones();
		}
		else {
			Simbolo nuevo = new Simbolo(caracter);
			simbolos.put(caracter,nuevo);
		}
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
	
	
	
	private void algoritmoHuffman(ArrayList<Simbolo>L) {
		//aca se clona
		ArrayList<Simbolo>auxLista = new ArrayList<Simbolo>() ;

		for(int i=0 ; i<L.size(); i++) {
			Simbolo s= new Simbolo();
			try {
				s=(Simbolo) (L.get(i)).clone();
				auxLista.add(s);
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
		}
		
		recursivoHuffman(L,auxLista,auxLista.size()-1);
		/*System.out.println("\n\nPost Huffman:");
		for(int i=0 ; i<auxLista.size(); i++) {
			Simbolo s= auxLista.get(i);
			System.out.println(s.getCaracter()+" codi="+s.getCodificacion()+" prob="+s.getProbabilidad());	
		}*/
	}
	
	//supone ArrayList probabilidades Ordenado
	private void recursivoHuffman(ArrayList<Simbolo>L,ArrayList<Simbolo>auxLista,int n) {
		Simbolo anteultimo,ultimo;
		if(n>1) {
			ultimo = auxLista.get(n);
			anteultimo = auxLista.get(n-1);
			
			System.out.println("ultimio\t"+(char)ultimo.getCaracter() +"\t" + ultimo.getProbabilidad());
			System.out.println("anteult\t" + (char)anteultimo.getCaracter()+ "\t" + anteultimo.getProbabilidad());
			
			Simbolo nuevo = new Simbolo('<'); // cualquier caracter
			nuevo.setProbabilidad(ultimo.getProbabilidad() + anteultimo.getProbabilidad());
			auxLista.remove(n);
			auxLista.remove(n-1);
			
			auxLista.add(n-1, (nuevo));
			
			Collections.sort(auxLista);
			for(int i=0 ; i<auxLista.size(); i++) {
				Simbolo s= auxLista.get(i);
				System.out.println(s.getCaracter()+" prob="+s.getProbabilidad());	
			}
			
			Scanner leer=new Scanner(System.in); 
			int num = leer.nextInt();
			
			recursivoHuffman(L,auxLista,n-1);
			//Vuelta:--
			//ultimo.setCodificacion(auxLista.get(n-1).getCodificacion()+"0");
			//anteultimo.setCodificacion(auxLista.get(n-1).getCodificacion()+"1");
			//auxLista.set(n-1, anteultimo);
			//auxLista.set(n, ultimo);
			
			
		}
		else { //n==1
			auxLista.get(1).addCaracter('1');
			auxLista.get(0).addCaracter('0');
		}
	}
	
	
	/*
		void ShannonFano(nodoSF vector[], int limInf, int limSup){
		    int i;
		    float totProb = 0, probAcum = 0;
		
		    if(limInf != (limSup-1)){
		        for(i=limInf; i<limSup; i++)
		            totProb+= vector[i].probabilidad;
		        i = limInf;
		        while(probAcum < (totProb/2)){
		            probAcum+= vector[i].probabilidad;
		            strcat((vector[i].codificacion),"1");
		            i++;
		        }
		        ShannonFano(vector,limInf,i);
		        int j = i;
		        while(probAcum < totProb){
		            probAcum += vector[j].probabilidad;
		            strcat(vector[j].codificacion,"0");
		            j++;
		        }
		        ShannonFano(vector,i,limSup);
		    }
		}
	 * */
	
	
}
