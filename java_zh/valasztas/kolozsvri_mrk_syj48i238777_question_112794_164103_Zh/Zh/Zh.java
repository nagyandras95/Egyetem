import java.util.*;
import java.lang.*;
import java.io.*;
import textit.*;

class Zh {
	public static void main(String[] args) {
		Valaszto jani = new Valaszto("Jani", "valami", 50, 12);
		Valaszto pisti = new Valaszto("Pisti", "valami2", 48, 40);
		Valaszto andi = new Valaszto("Andi", "valami3", 25, 18);
		ArraySzavazorendszer valasztorendszer = new ArraySzavazorendszer();
		
		valasztorendszer.szavaz(jani, Part.JavaHosok);
		valasztorendszer.szavaz(pisti, Part.JavaHosok);
		valasztorendszer.szavaz(jani, Part.CppFanok);
		valasztorendszer.szavaz(andi, Part.HaskellMagusok);
		valasztorendszer.lezar();
		
		System.out.println(valasztorendszer.osszSzavazat());
		if(valasztorendszer.nyertes() == Part.CppFanok) System.out.println("CppFanok");
		else if(valasztorendszer.nyertes() == Part.JavaHosok) System.out.println("JavaHosok");
		else if(valasztorendszer.nyertes() == Part.HaskellMagusok) System.out.println("HaskellMagusok");
		
	}
}