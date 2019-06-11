package valasztas;

public class Main {
	public static void main(String[] args) throws NoResults { // <-- TODO
		Szavazorendszer<PolgarKulcs> a = new HashSzavazorendszer<PolgarKulcs>();
		
		Szavazo p1 = new Szavazo("Pista", "001", 19, 36);
		Szavazo p2 = new Szavazo("Anna", "002", 21, 36);
		Szavazo p3 = new Szavazo("Peti", "003", 20, 36);
		
		// a.lezar();
		szavazWrapper(a, p1, Part.JavaHosok);
		szavazWrapper(a, p2, Part.JavaHosok);
		szavazWrapper(a, p1, Part.CppFanok);
		// szavazWrapper(a, p3, Part.HaskellMagusok);	
		
		a.lezar();
		System.out.println("Osszesen: " + a.osszSzavazat());
		
		try {
			System.out.println("Nyertes: " + a.nyertes());
		} catch(NoResults e) {
			System.out.println("A szavazas meg nincs lezarva");
		}
	}
	
	private static void szavazWrapper(Szavazorendszer<PolgarKulcs> r, Szavazo sz, Part p) {
		try {
			r.szavaz(sz, p);
		} catch (AlreadyVoted e) {
			System.out.println("Mar szavazott: " + e.getKulcs() + "\n");
		} catch (CannotVote e) {
			System.out.println("Mar nem szavazhat: " + e.getKulcs() + "\n");
		}
	}
}