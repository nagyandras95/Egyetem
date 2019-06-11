package textit;
import java.io.*;
public class Polgarok{
	private String nev;
	private String azon;
	private int kor;
	private int orszagkod;
	
	public void setNev(String _nev){
			this.nev = _nev;
	}
	public void setAzon(String _azon){
			this.azon = _azon;
	}
	public void setKor(int _kor){
			this.kor = _kor;
	}
	public void setOrszagKod(int _kod){
		this.orszagkod = _kod;
	}
	
	public String getNev() { return nev; }
	public String getAzon() { return azon;}
	public int getKor() { return kor;}
	public int getOrszagKod() { return orszagkod;}
	
	public Polgarok(String _nev, String _azon, int _kor, int _orszagkod){
		this.nev = _nev;
		this.azon = _azon;
		this.kor = _kor;
		this.orszagkod = _orszagkod;
	}
}
