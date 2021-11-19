package algoritmos;

public class Simbolo implements Comparable<Simbolo>{
	private char caracter;
	private int apariciones;
	private float probabilidad;
	private String codificacion="";
	
	public Simbolo(char caracter){
		this.caracter=caracter;
		this.apariciones=1;
		this.probabilidad=0;
	}
	
	public Simbolo(String codificacion){
		this.codificacion=codificacion;
		this.apariciones=1;
		this.probabilidad=0;
	}
	
	public Simbolo(){
	}
	
	public void incrementarApariciones() {
		this.apariciones++;
	}

	public char getCaracter() {
		return caracter;
	}

	public int getApariciones() {
		return apariciones;
	}

	public float getProbabilidad() {
		return probabilidad;
	}

	public void setProbabilidad(float probabilidad) {
		this.probabilidad = probabilidad;
	}
	
	
	public String getCodificacion() {
		return codificacion;
	}

	public void setCodificacion(String codificacion) {
		this.codificacion = codificacion;
	}
	public void addCaracter(char caracter) {
		this.codificacion+= caracter;
	}

	@Override
	public int compareTo(Simbolo o) {
		if(this.probabilidad >= o.getProbabilidad() ) {
			return -1;
		}
		else{
			return 1;
		}
	}
	
}
