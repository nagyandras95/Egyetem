package textit;

import java.util.*;
import java.lang.*;
import java.io.*;



public class ArraySzavazorendszer {
	
	public ArraySzavazorendszer() {
		this.lezart = false;
	}
	
	public int getSzavazatokSzama() {
		return szavazatokdb;
	}
	
	public void szavaz(Valaszto v, Part p) {
		Szavazatok szavazo = null;
		switch(p) {
			case JavaHosok:
				szavazo = new Szavazatok(v.getAzon(), Part.JavaHosok);
				break;
			case CppFanok:
				szavazo = new Szavazatok(v.getAzon(), Part.CppFanok);
				break;
			case HaskellMagusok:
				szavazo = new Szavazatok(v.getAzon(), Part.HaskellMagusok);
				break;
		}
		
		if(!lezart && szavazo != null && !szavazatok.contains(szavazo) && !v.getSzavazott()) {
			szavazatok.add(szavazo);
			szavazatokdb++;
			if(p == Part.CppFanok) cpp++;
			else if(p == Part.HaskellMagusok) haskell++;
			else if(p == Part.JavaHosok) java++;
			v.setSzavazott();
		}
		else System.out.println("Hiba"); //todo kivételkezelés
		//throw new ArithmeticException("Lezart szavazas vagy mar szavazott");
	}
	
	public int osszSzavazat() {
		return szavazatokdb;
	}
	
	public int hanySzavazat(Part p) {
		if(lezart) {
			switch(p) {
				case JavaHosok:
					return java;
				case CppFanok:
					return cpp;
				case HaskellMagusok:
					return haskell;
				default:
					return -1;
			}
		} else {
			System.out.println("Hiba");
			return -1;			//exception
		}
	}
	
	
	public Part nyertes() {
		if(lezart){
			if(java > cpp && java > haskell) return Part.JavaHosok;
			else if(cpp > java && cpp > haskell) return Part.CppFanok;
			else return Part.HaskellMagusok;
		} else {
			System.out.println("Hiba"); //exception
			return null;
		}
	}

	
	
	
	
	public void lezar() {
		this.lezart = true;
	}
	
	private boolean lezart = false;
	private static int szavazatokdb = 0;
	private static int cpp = 0;
	private static int haskell = 0;
	private static int java = 0;
	private ArrayList<Szavazatok> szavazatok = new ArrayList<Szavazatok>();
	
}

class Szavazatok {
	public Szavazatok(String azon, Part p) {
		this.azon = azon;
		this.p = p;
	}
	
	protected String azon;
	protected Part p;
}