package algoritmos;


import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;

public class RLC {
	/*if(nombreArchivo.contains(".raw")) {
		    System.out.println("Es .raw");
		    
		}
		if(nombreArchivo.contains(".txt")) {
		    System.out.println("Es .txt");
		}*/

	public void compresionRLC(String nombreArchivo) {
	    File archivo = null;
	    FileReader fr = null;
	    
	    FileWriter fichero = null;
        PrintWriter pw = null;

		try {
			archivo = new File (nombreArchivo);
	        fr = new FileReader (archivo);

	        fichero = new FileWriter(nombreArchivo +".RLC");
            pw = new PrintWriter(fichero);

			
			
			//cada algoritmo (input)
			int caracter = fr.read();
			char anterior = (char)caracter;
			int apariciones=1;
			
			
			while (caracter!=-1) {
				//System.out.println((char) caracter);
                //pw.println((char) caracter);
				caracter = fr.read();
				char actual  = (char) caracter;
				if(actual!='\n' && actual!='\0' && actual!=13) {
					if(anterior != actual) {
						pw.print(anterior);
						pw.println(apariciones);
						anterior=actual;
						apariciones=1;
					}
					else {
						apariciones++;
					}
				}
				else {
					//pw.println("caracter invisible " + (int)actual);
				}
            }
			fr.close();
			pw.close();
		}catch(Exception ex) {
			ex.printStackTrace();
		}
	}
}