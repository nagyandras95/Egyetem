package valasztas;
import java.util.Map;
import java.util.HashMap;

public class HashSzavazorendszer<V> implements Szavazorendszer<V> {
	
	private Map<V,Partok> szavazatok;
	//~ private List<String> szavaztak;
	private boolean lezart;
	
	public HashSzavazorendszer() { 
		szavazatok = new HashMap<>();
		//~ szavaztak = new ArrayList<>();
		lezart = false;
	}
	
	public void szavaz(Azonosithato<V> polgar, Partok part) {
		if (lezart) {
			throw new RuntimeException("A szavazas le van zarva");
		} else {
			
			if (szavazatok.containsKey(polgar.getKulcs())) {
				throw new AlreadyVoted(polgar.getKulcs().hashCode());
			} else {
				szavazatok.put(polgar.getKulcs(), part);
			}
		}
	}
	
	public Integer osszSzavazat() {
		return szavazatok.size();
	}
	
	public void lezar() {
		lezart = true;
	}
	
	public Integer hanySzavazat(Partok part) {
		if (lezart) {
			int sum = 0;
			for (Partok p: szavazatok.values()) {
				if (p == part) {
					sum += 1;
				}
			}
			return sum;
		} else {
			throw new RuntimeException("Meg nincs lezarva");
		}
	}
	
	public Partok nyertes() {
		if (! lezart) {
			throw new RuntimeException("Meg nincs lezarva");
		}
		
		Integer java = hanySzavazat(Partok.JAVA_HOSOK);
		Integer cpp = hanySzavazat(Partok.CPP_FANOK);
		Integer haskell = hanySzavazat(Partok.HASKELL_MAGUSOK);
		
		if ( (java >= cpp) && (java >= haskell) ){
			return Partok.JAVA_HOSOK;
		}
		
		if ( (cpp >= java) && (cpp >= haskell) ) {
			return Partok.CPP_FANOK;
		}
		
		return Partok.HASKELL_MAGUSOK;
		
	
	}
}

