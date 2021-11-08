package algoritmos;

public class Simbolo implements Comparable,Cloneable{
	private char caracter;
	private int apariciones;
	private float probabilidad;
	private String codificacion="";
	
	public Simbolo(char caracter){
		this.caracter=caracter;
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
	
	
	

	@Override
	protected Object clone() throws CloneNotSupportedException {
		try {
			Simbolo nuevo = (Simbolo) super.clone();
			return nuevo;
		}
		catch(CloneNotSupportedException e) {
			throw new InternalError(e.toString());
		}
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
	public int compareTo(Object o) {
		Simbolo s= (Simbolo) o;
		if(this.probabilidad >= s.getProbabilidad() ) {
			return -1;
		}
		else{
			return 1;
		}
	}
	
}
