import textit.*;
import java.io.*;
import java.*;
class zh{
	public static void main(String[] args){
		Polgarok elso = new Polgarok("Béla","123A", 22, 43);
		Polgarok masodik = new Polgarok("Jenő", "245B", 33, 43);
		Polgarok harmadik = new Polgarok("Juliska", "545C", 44, 43);
		ArraySzavazorendszer ar = new ArraySzavazorendszer();
		
		ar.szavaz(elso,Partok.JavaHosok);
		ar.szavaz(masodik,Partok.JavaHosok);
		ar.szavaz(elso,Partok.CppFanok); 
		ar.szavaz(harmadik,Partok.HaskellMagusok);
		ar.lezar();
		System.out.println("Hanyan szavaztak: "+ ar.osszSzavazat());
		System.out.println("Nyertes part: "+ar.nyertes());
	}
}

