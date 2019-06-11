import valasztas.Polgar;
import valasztas.ArraySzavazorendszer;
import valasztas.HashSzavazorendszer;
import valasztas.Partok;
import valasztas.Szavazorendszer;
import valasztas.PolgarKulcs;

public class main {
	
	public static void main (String[] args) {
		//~ System.out.println("Hello");
		
		try {
		
			Polgar<PolgarKulcs> p1 = new Polgar<>("Laci", 20, new PolgarKulcs("702311DE", 6));
			Polgar<PolgarKulcs> p2 = new Polgar<>("Béla", 20, new PolgarKulcs("702312DE", 4));
			Polgar<PolgarKulcs> p3 = new Polgar<>("Sándor", 20, new PolgarKulcs("702313DE", 6));
			
			Szavazorendszer<PolgarKulcs> szav = new ArraySzavazorendszer<>();
			
			szav.szavaz(p1, Partok.JAVA_HOSOK);	
			szav.szavaz(p2, Partok.JAVA_HOSOK);
			//~ szav.szavaz(p1, Partok.CPP_FANOK);
			szav.szavaz(p3, Partok.HASKELL_MAGUSOK);
			szav.lezar();
			System.out.println(szav.osszSzavazat());
			System.out.println(szav.nyertes());
			
		} catch(Exception e) {
			System.out.println(e);
		}
	}
}
