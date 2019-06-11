package textit;

import java.util.*;
import java.lang.*;
import java.io.*;

public class Valaszto {
	
	public Valaszto(){}
	
	public Valaszto(String nev, String azon, int kor, int kod) {
		this.nev = nev;
		this.azon = azon;
		this.kor = kor;
		this.kod = kod;
	}
	
	public void setNev(String nev) {
		this.nev = nev;
	}
	
	public void setAzon(String azon) {
		this.azon = azon;
	}
	
	public void setKor(int kor) {
		this.kor = kor;
	}
	
	public void setKod(int kod) {
		this.kod = kod;
	}
	
	public void setSzavazott() {
		this.szavazott = true;
	}
	
	public String getNev() {
		return this.nev;
	}
	
	public String getAzon() {
		return this.azon;
	}
	
	public int getKor() {
		return this.kor;
	}
	
	public int getKod() {
		return this.kod;
	}
	
	public boolean getSzavazott() {
		return this.szavazott;
	}

	@Override
	public boolean equals(Object f) {
		if(f != null && this.getClass().equals(f.getClass())) {
			Valaszto f2 = (Valaszto) f;
			return f2.azon == this.azon;
		}
		else return false;
	}
	
	
	protected String nev;
	protected String azon;
	protected int kor;
	protected int kod;
	protected boolean szavazott = false;
	
}